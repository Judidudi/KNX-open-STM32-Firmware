# KNX-open-Firmware-Stack – Codebase Guide

## Project Overview

STM32-Firmware für KNX-kompatible Geräte, die mit dem
KNX open Developer Tool (separates Repository) konfiguriert und
programmiert werden. Die Firmware implementiert einen eigenen KNX-TP-Stack
auf dem STM32F446RE mit dem NCN5120-Transceiver.

Lizenz: GPLv3
Primärer MCU: STM32F446RE (Cortex-M4, 180 MHz)
KNX-Transceiver: NCN5120 (UART-Interface, TPUART-kompatibel)

## Two-Repo-Architektur

| Repo                       | Inhalt                              |
|----------------------------|-------------------------------------|
| KNX-open-Developer-Tool    | Qt6-Konfigurationstool (ETS-Pendant)|
| dieses Repo                | STM32-Firmware                      |

Die beiden Repos teilen sich genau einen Vertrag: das YAML-Gerätemanifest
(catalog/devices/*.yaml im Tool-Repo). Es definiert alle Speicheradressen,
Parameter-Offsets und ComObject-Nummern, auf die BEIDE Seiten angewiesen
sind. Niemals Speicheroffsets auf einer Seite ändern, ohne die andere Seite
zu synchronisieren.

## Build

Anforderungen: STM32CubeIDE (generiertes Makefile), arm-none-eabi-gcc >= 12

    # Release-Build:
    make -j$(nproc) all

    # Debug-Build:
    make -j$(nproc) DEBUG=1 all

Das Makefile wird von STM32CubeIDE verwaltet. Manuelle Änderungen außerhalb
der Projektdatei (.ioc) können bei einem Resync überschrieben werden.
Anpassungen möglichst über CubeIDE vornehmen.

## Flash & Debug

Primäres Tool: STM32CubeProgrammer (SWD-Interface via ST-Link V2)

    # Flash via CLI:
    STM32_Programmer_CLI -c port=SWD -w build/firmware.hex -v -rst

    # Alternativ: openocd
    openocd -f interface/stlink.cfg -f target/stm32f4x.cfg \
            -c "program build/firmware.elf verify reset exit"

Debugging: STM32CubeIDE mit integriertem GDB-Server, oder VS Code mit
cortex-debug Extension + ST-Link.

## Architektur (Modulübersicht)

    src/
    ├── knx/
    │   ├── KnxStack.c/h          # Haupt-Loop: Frame empfangen/senden
    │   ├── KnxTpUart.c/h         # UART-Treiber für NCN5120 (TPUART-Protokoll)
    │   ├── KnxAddressTable.c/h   # Lesen der Adresstabelle aus Flash
    │   ├── KnxAssocTable.c/h     # ComObject <-> GA-Zuordnung
    │   ├── KnxComObject.c/h      # ComObject-Verwaltung, Flags (C/R/W/T/U)
    │   ├── KnxProgramming.c/h    # Programmiermodus-LED, A_IndividualAddress_Write
    │   └── CemiFrame.c/h         # CEMI L_Data En-/Dekodierung
    ├── app/
    │   ├── Application.c/h       # App-Initialisierung, Haupt-Loop
    │   ├── SwitchActuator.c/h    # Beispielapplikation: Schaltaktor
    │   └── Parameters.h          # Parameter-Defines (mit Manifest synchronisiert)
    └── main.c

## Schlüsselkonzept: Gemeinsamer Speicher-Vertrag

Der KNX-Programmierprozess schreibt drei Speicherbereiche vom Tool auf das
Gerät (via A_Memory_Write). Die Basisadressen kommen aus dem Manifest:

    Adresstabelle  (manifest: memoryLayout.addressTable,    Standard: 0x4000)
      [0] count_hi / count_lo      <- 1 + Anzahl Gruppenadressen
      [1] PA_hi / PA_lo            <- physikalische Adresse des Geräts
      [2..n] GA_hi / GA_lo         <- Gruppenadressen (Reihenfolge = Assoc-Index)

    Assoziationstabelle  (manifest: memoryLayout.associationTable, Standard: 0x4100)
      [0] count_hi / count_lo      <- Anzahl Einträge
      [k] ga_index / co_number     <- 1-basierter GA-Index + ComObject-Nummer

    Parameterblock  (manifest: memoryLayout.parameterBase,  Standard: 0x4400)
      Rohe Bytes an Offsets, die pro Parameter im Manifest stehen
      (parameters[].memoryOffset, parameters[].size)

In der Firmware werden diese Bereiche aus Flash gelesen:

    // Beispiel: Parameter lesen (Offset aus Manifest parameters[].memoryOffset)
    uint16_t startupDelay = KNX_PARAM_READ_U16(KNX_PARAM_BASE + P_STARTUP_DELAY_OFFSET);

## Parameter-API

Parameter-Offsets werden als manuelle `#define`-Konstanten in `src/app/Parameters.h`
gepflegt und mit dem YAML-Manifest synchronisiert. Jeder Offset trägt den Kommentar
`// manifest: parameters[id=<id>].memoryOffset`, damit die Zuordnung nachvollziehbar
bleibt.

    // Beispiel in Parameters.h:
    #define P_STARTUP_DELAY_OFFSET  0U  // manifest: parameters[id=p_startup_delay].memoryOffset

## ComObject-Nummern

Jedes ComObject im Manifest hat ein "number"-Feld, das exakt dem Index
in der Firmware-ComObject-Tabelle entsprechen muss:

    # Manifest:
    comObjects:
      - id: co_switch_ch1
        number: 0        # <- ComObject-Index 0 in der Firmware
        dpt: "1.001"

    // Firmware: ComObject 0 empfängt GroupValueWrite -> Relais schalten
    KNX_ComObject_OnWrite(0, value, len);  // Callback für CO-Index 0

## Programmiermodus

Das Gerät tritt in den Programmiermodus, wenn der physikalische Prog-Taster
gedrückt wird. Die Prog-LED leuchtet dann.

Im Programmiermodus akzeptiert das Gerät:
  1. A_IndividualAddress_Write  -> setzt physikalische Adresse
  2. A_Memory_Write             -> schreibt Adresstabelle, Assoziationstabelle,
                                   Parameterblock an die im Manifest definierten Adressen
  3. A_Restart                  -> Neustart, verlässt Programmiermodus

## Code Style

- C99, HAL-basiert (CubeMX-generiert)
- Präfix KNX_ für alle KNX-Stack-Funktionen
- Präfix APP_ für applikationsspezifischen Code
- Keine dynamische Speicherverwaltung (malloc/free verboten)
- Interrupts so kurz wie möglich; Verarbeitung im Haupt-Loop via Flags
- Alle magischen Zahlen als #define mit Quellenangabe (Manifest oder KNX-Spec)

## Neues Gerät hinzufügen

1. YAML-Manifest in catalog/devices/<id>.yaml im Tool-Repo erstellen
2. ComObject-Nummern (number-Feld) und Parameter-Offsets festlegen
3. Parameters.h im Firmware-Repo mit denselben Offsets synchronisieren
4. App-Modul in src/app/ anlegen, ComObject-Callbacks registrieren
5. Kein Makefile-/CubeIDE-Projektänderung nötig, solange keine neuen
   HAL-Peripherals hinzukommen

## Verknüpfung mit dem Developer Tool

Das Tool-Repo liest Manifeste aus KNXODT_CATALOG_PATH. Für gemeinsame
Entwicklung beider Repos:

    export KNXODT_CATALOG_PATH=/pfad/zu/diesem-repo/catalog/devices

Dann lädt das Tool die Manifeste direkt aus dem Firmware-Repo.
