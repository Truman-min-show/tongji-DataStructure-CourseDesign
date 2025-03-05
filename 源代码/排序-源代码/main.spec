# -*- mode: python ; coding: utf-8 -*-
import os
added_files=[('C:\\Users\\lenovo\\Desktop\\Sorting-Algorithms-Visualizer-master\\res'),
('C:\\Users\\lenovo\\Desktop\\Sorting-Algorithms-Visualizer-master\\src\\algorithms','C:\\Users\\lenovo\\Desktop\\Sorting-Algorithms-Visualizer-master\\src'),
    (('C:\\Users\\lenovo\\Desktop\\Sorting-Algorithms-Visualizer-master\\venv\\Lib\\site-packages'))]

a = Analysis(
    ['src\\main.py','src\\algs.py','src\\display.py',
    'src\\algorithms\\__init__.py',
    'src\\algorithms\\binaryinsertionSort.py',
    'src\\algorithms\\insertionSort.py',
    'src\\algorithms\\bubbleSort.py',
    'src\\algorithms\\quickSort.py',
    'src\\algorithms\\shellSort.py',
    'src\\algorithms\\selectionSort.py',
    ],
    pathex=[],
    binaries=[],
    datas=[],
    hiddenimports=['pygame'],
    hookspath=[],
    hooksconfig={},
    runtime_hooks=[],
    excludes=[],
    noarchive=False,
    optimize=0,
)
pyz = PYZ(a.pure)

exe = EXE(
    pyz,
    a.scripts,
    a.binaries,
    a.datas,
    [],
    name='main',
    debug=False,
    bootloader_ignore_signals=False,
    strip=False,
    upx=True,
    upx_exclude=[],
    runtime_tmpdir=None,
    console=True,
    disable_windowed_traceback=False,
    argv_emulation=False,
    target_arch=None,
    codesign_identity=None,
    entitlements_file=None,
)
