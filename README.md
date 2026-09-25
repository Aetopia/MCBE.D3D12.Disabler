# MCBE D3D12 Disabler

Safely prevents Minecraft: Bedrock Edition from using D3D12.

## Usage
- [Download](https://github.com/Aetopia/MCBE.D3D12.Disabler/releases/latest/download/vcruntime140_1.dll) the latest release of MCBE D3D12 Disabler.

- Run the following command in PowerShell to find where the game is located:

    ```powershell
    & "$ENV:SystemRoot\explorer.exe" "$((Get-AppxPackage "Microsoft.MinecraftUWP").InstallLocation)"
    ```

- Place the dynamic link library in the opened folder & launch the game.

## Build

1. Install [CMake](https://cmake.org) & [MinGW (x64)](https://www.mingw-w64.org).

2. Run [`BUILD.cmd`](BUILD.cmd) to build the project.