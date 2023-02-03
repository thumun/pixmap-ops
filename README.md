# pixmap-ops

Image manipulation demos based on the PPM image format.

TODO: Add a representative image for your project here

## How to build

*Windows*

Open git bash to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake -G "Visual Studio 17 2022" ..
pixmap-ops/build $ start pixmap-ops.sln
```

Your solution file should contain two projects: `pixmap_art` and `pixmap_test`.
To run from the git bash command shell, 

```
pixmap-ops/build $ ../bin/Debug/pixmap_test
pixmap-ops/build $ ../bin/Debug/pixmap_art
```

*macOS*

Open terminal to the directory containing this repository.

```
pixmap-ops $ mkdir build
pixmap-ops $ cd build
pixmap-ops/build $ cmake ..
pixmap-ops/build $ make
```

To run each program from build, you would type

```
pixmap-ops/build $ ../bin/pixmap_test
pixmap-ops/build $ ../bin/pixmap_art
```

## Image operators

Resize 
![resize](https://github.com/thumun/pixmap-ops/blob/main/Img_Op_pictures/earth-200-300.png)
Alphablend 
![alphablend](https://github.com/thumun/pixmap-ops/blob/main/Img_Op_pictures/earth-blend-0.5.png)
Flip 
![flip](https://github.com/thumun/pixmap-ops/blob/main/Img_Op_pictures/earth-flip.png)
Gamma Correction [0.6] 
![gamma0.6](https://github.com/thumun/pixmap-ops/blob/main/Img_Op_pictures/earth-gamma-0.6.png)
Gamma Correction [2.2] 
![gamma2.2](https://github.com/thumun/pixmap-ops/blob/main/Img_Op_pictures/earth-gamma-2.2.png)
Greyscale
![greyscale](https://github.com/thumun/pixmap-ops/blob/main/Img_Op_pictures/earth-grayscale.png)
Subimage
![subimage](https://github.com/thumun/pixmap-ops/blob/main/Img_Op_pictures/earth-subimage.png)

## Results

TODO: Show artworks using your class

