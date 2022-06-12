# Backend Agnostic Tree-Based Tiling Window Manager
- Paritions space by allocating space for WindowNodes automatically
- Aims to provide a platform for writing window managers that abstracts the specific implementation away
- Will (in future) be able to manage windows for multiple windowing system implementations


<br>
<br>
<br>

# Build Steps

- select [WinterFace_SGL_Client] or [xClient] build target
- build and run with cmake
> For xClient, please refer to the Demo section for more info

<br>
<br>
<br>

# Demo
## [WinterFace_SGL_Client]
- Click "Add" in the toolbar of the SGL window that appears
- A tree of windows will be built incrementally, adding one each time you click the button!
## [xClient]
### xClient is intended as a proof of concept, it may not function well or at all.
#### Reason: no icccm, no reparenting support, no framing support, no global key binding support, no
- Be on Linux
- Install packages required by the script
- Build xClient
- cd into src/XServer/XClient
- `./run.sh`
- other programs can be run on the the Xephyr X server by running them with the dispaly environment variable set to where the X server is running. EX: `DISPLAY=:9 alacritty` to run `alacritty` on dispaly `:9`
- > Automatic X server detection is disabled in XServer.cpp, the WM will always attempt to connect to the X server running on display `:9`

> Reach out via the group discord channel if there are build issues!