# christmast-tree-lights

ESP32 powered controller for WS2812 based pixel LED strip (chain) with HTTP API and GitHub Actions workflow for OTA.

> **Prerequisites** 
>
> Install [Visual Studio Code](https://code.visualstudio.com/) with [PlatformIO extension](https://platformio.org/install/ide?install=vscode).

## Quick start

### First setup

1. Clone the repo and open it in Visual Studio Code. Platformio should automatically install all project dependencies.

2. Rename `credentials-template.h` to `credentials.h` and type your WiFi an Husarnet credentials there (you will find you Husarnet Join Code at https://app.husarnet.com).

4. Click "PlatformIO: upload" button to flash your ESP32 board connected to your laptop. You will find the following log in the serial monitor:

    ```bash
    **************************************
    Christmas Tree Lights
    **************************************
    
    📻 1. Connecting to: FreeWifi Wi-Fi network .. done

    ⌛ 2. Waiting for Husarnet to be ready ... done

    🚀 HTTP server started

    Visit:
    http://pixel-led-chain:8080/

    Known hosts:
    my-laptop (fc94:a4c1:1f22:ab3b:b04a:1a3b:ba15:84bc)
    pixel-led-chain (fc94:f632:c8d9:d2a6:ad18:ed16:ed7e:9f3f)
    ```

5. HTTP API examples:

    - `curl http://pixel-led-chain:8080/mode=0` - set `modeRGB=0`(rainbow theme)
    - `curl http://pixel-led-chain:8080/color=red` - set `modeRGB=5` and `rgb={255,0,0}` (all LEDs red)
    - `curl http://pixel-led-chain:8080/color=yellow` - set `modeRGB=5` and `rgb={255,255,0}` (all LEDs yellow):
    - `curl http://pixel-led-chain:8080/color=green` - set `modeRGB=5` and `rgb={0,255,0}` (all LEDs green):


### Internet OTA with GitHub Actions

1. Create the folowing GitHub repository secrets (`Settings` > `Secrets` > `New repository secret`):

    | Secret | Sample Value | Desription |
    | - | - | - |
    | `WIFI_SSID` | FreeWifi | just your WiFi network name |
    | `WIFI_PASS` | hardtoguess | ... and password |
    | `HUSARNET_JOINCODE` | fc94:...:932a/xhfqwPxxxetyCExsSPRPn9 | find your own **secret** Join Code at your user account at https://app/husarnet.com > `choosen network` >  `add element` button. Anyone with this Join Code can connect to your Husarnet network |

2. Push changes to your repo:

    ```bash
    git add *
    git commit -m "triggering the workflow"
    git push
    ```

3. In ~3 minutes the GitHub workflow should finish its job. Visit: `http://my-esp32:8080` URL with a sample "Hello world" website hosted by your ESP32.


    Of course your laptop need to be connected to the same Husarnet network - you will find quick start guide showing how to do it here: https://husarnet.com/docs/


## Tips

### Erasing flash memory of ESP32

1. Connect ESP32 to your laptop

2. Install platformio CLI

    ```bash
    pip install -U platformio
    ```

3. Make flash erase:

    ```bash
    pio run --target erase
    ```

### Monitoring network traffic on `hnet0` interface

```bash
sudo tcpflow -p -c -i hnet0
```

### Accesing a webserver hosted by ESP32 using a public domain

Here is a blog post showing how to configure Nginx Proxy Manager to **provide a public access to web servers hosted by Husarnet connected devices**: https://husarnet.com/blog/reverse-proxy-gui

It can be also used  o provide the access to a web server hosted by ESP32 using a nice looking link like: `https://my-awesome-esp32.mydomain.com`.