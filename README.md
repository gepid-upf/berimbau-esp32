# berimbau-esp32

Berimbau-like toy with gamification to aid with musical rythm and pulse education. It uses an ESP32 as it's main microcontroller. The audio is handled by the 2 DAC channels and is interrupt-based with digital mixing and SFX (muffling effect that emulates the ressonance box of the berimbau based on the distance captured by an URM37). It also uses the SPIFFS for saving the recorded sequences to be repeated by the user.

## Getting Started

### Compiling

You will need ESP-IDF to compile this. Please refer to [ESP-IDF](https://docs.espressif.com/projects/esp-idf/en/latest/get-started/index.html) to install. To compile, clone this repo recursively with all submodules, and run
```
make flash
```

### Assemblying the components

The [schematic](docs/schematic/berimbau.sch) was made using EagleCAD student version. There you can find how the components are connected. If you do not want to download EagleCAD or do not have a license, please refer to this [pdf schematic](docs/schematic/berimbau.pdf).

### Making the PCB

This is completely optional, but recommended. The PCB was made using a Roland EGX-350 router with the software CopperCAM. Please refer to the [PCB project](docs/schematic/berimbau.cam).

### Editing the Flash contents

There is a tool to edit the contents of the flash memory and dump the utilization logs. You can find it at [berimbau-tool-gui](https://github.com/gepid-upf/berimbau-tool-gui).

## Authors

* **Angelo Elias Dalzotto** - *Berimbau Interface and Game, Audio Library, URM37 driver, LED and button control* - [aedalzotto](https://github.com/aedalzotto)

## Acknowledgements

* **Boris Lovosevic** - *[ESP32_TFT_library](https://github.com/loboris/ESP32_TFT_library)* - [loboris](https://github.com/loboris)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details.
