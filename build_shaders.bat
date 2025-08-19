@echo off
setlocal enabledelayedexpansion

:: Directories
set SRC_DIR=src\shaders\shader_src
set SPV_DIR=src\shaders\spv
set DXIL_DIR=src\shaders\dxil

:: Create output directories if they don’t exist
if not exist "%SPV_DIR%" mkdir "%SPV_DIR%"
if not exist "%DXIL_DIR%" mkdir "%DXIL_DIR%"

echo ==========================
echo Compiling Vulkan shaders...
echo ==========================

for %%f in (%SRC_DIR%\*.vert %SRC_DIR%\*.frag) do (
    if exist "%%f" (
        set "name=%%~nxf"
        echo glslc "%%f" -o "%SPV_DIR%\!name!.spv"
        glslc "%%f" -o "%SPV_DIR%\!name!.spv"
        echo [OK] %%f → %SPV_DIR%\!name!.spv
    )
)

echo ==========================
echo Converting to Direct3D...
echo ==========================

for %%f in (%SRC_DIR%\*.vert %SRC_DIR%\*.frag) do (
    if exist "%%f" (
        set "name=%%~nxf"
        echo spirv-cross "%SPV_DIR%\!name!.spv" --hlsl --shader-model 60 --output "%DXIL_DIR%\!name!.hlsl"
        spirv-cross "%SPV_DIR%\!name!.spv" --hlsl --shader-model 60 --output "%DXIL_DIR%\!name!.hlsl"

        :: Decide shader type (-T) based on extension
        set "ext=%%~xf"
        if /I "!ext!"==".vert" (
            dxc "%DXIL_DIR%\!name!.hlsl" -T vs_6_0 -Fo "%DXIL_DIR%\!name!.dxil"
        ) else (
            dxc "%DXIL_DIR%\!name!.hlsl" -T ps_6_0 -Fo "%DXIL_DIR%\!name!.dxil"
        )
        echo [OK] %%f → %DXIL_DIR%\!name!.dxil
    )
)

echo.
echo All shaders compiled successfully!
pause
