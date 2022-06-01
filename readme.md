# Backend Agnostic Tree-Based Tiling Window Manager
- Paritions space by allocating space for WindowNodes automatically
- Aims to provide a platform for writing window managers that abstracts the specific implementation away
- Will (in future) be able to manage windows for multiple windowing system implementations


<br>
<br>
<br>

# Build Steps

- select [WindowTrees] build target
- select [SGL_Client] launch target
- build and run with cmake

<br>
<br>
<br>

# Demo
- Click "Add" in the toolbar of the SGL window that appears
>A tree of windows will be built incrementally, adding one each time you click the button!