# lightDenseYOLO

A real-time object detection app based on lightDenseYOLO
Our lightDenseYOLO is the combination of two components: **lightDenseNet** as the CNN feature extractor and **YOLO v2** as the detection module

lightDenseYOLO was trained with two famous object detection datasets (MS COCO and Pascal VOC 07+12)

| CNN architecture          	    | Training Data 	| mAP  	    | Processing time  	    |
|---------------------------	    |---------------	|---------	|-----------------------|
| **lightDenseYOLO (2 blocks)** 	| VOC           	| **70.7** 	| **20 ms ~ 50 fps**   	|
| **lightDenseYOLO (4 blocks)** 	| VOC           	| **77.1** 	| **28 ms ~ 35.8 fps** 	|
| YOLO v2                   	    | VOC           	| 75.4 	    | 30 ms ~ 33 fps   	    |
| Faster-RCNN + Resnet 101  	    | VOC           	| 78.9 	    | 200 ms ~ 5 fps   	    |
| MobileNets + SSD          	    | VOC           	| 73.9 	    | 80 ms ~ 12.5 fps 	    | 
| **lightDenseYOLO (2 blocks)** 	| VOC + COCO    	| **79.0** 	| **20 ms ~ 50 fps**   	|
| **lightDenseYOLO (4 blocks)** 	| VOC + COCO    	| **82.5** 	| **28 ms ~ 35.8 fps** 	|
| YOLO v2                   	    | VOC + COCO    	| 81.5 	    | 30 ms ~ 33 fps   	    |
| Faster-RCNN + Resnet 101  	    | VOC + COCO    	| 83.8 	    | 200 ms ~ 5 fps   	    |
| MobileNets + SSD          	    | VOC + COCO    	| 76.6 	    | 80 ms ~ 12.5 fps 	    |

# Usage

**Requirements:**
+ Ubuntu 16.04+
+ C++ 11 complier
+ QT 5.7.0 and QT Creator 4.0.2
+ Open CV 3.2 +
+ GPU (NVIDIA Gefore 1070+)

**Installation**
+ [Install CUDA, CUDNN](http://www.python36.com/how-to-install-tensorflow-gpu-with-cuda-9-2-for-python-on-ubuntu/)
+ [Install OpenCV](http://www.python36.com/how-to-install-tensorflow-gpu-with-cuda-9-2-for-python-on-ubuntu/)
+ [Install QT by terminal](https://wiki.qt.io/Install_Qt_5_on_Ubuntu)
+ Make sure to install OpenCV, CUDA, CUDNN perfectly and try to build [DarkNet](https://github.com/AlexeyAB/darknet)
+ Download the weight files [link](https://www.dropbox.com/s/92mnurujtjtywcr/lightDenseYOLO.zip?dl=0).

**Build:**
+ Create a new Qt project,
+ Copy all existing file in the project folder. 
+ Create a new folder named **data** next to the create project folder and copy the weight file and the cfg file there.
+ Hit build and run.

**Example video**
+ [Youtube link](https://www.youtube.com/watch?v=XfbD2THhfiY&feature=youtu.be)

# References
1.[LightDenseYOLO: A Fast and Accurate Marker Tracker for Autonomous UAV Landing by Visible Light Camera Sensor on Drone](http://www.mdpi.com/1424-8220/18/6/1703)

2.[YOLO 9000](https://arxiv.org/abs/1612.08242)

3.[Faster-RCNN](https://arxiv.org/abs/1506.01497)

4.[MobileNets](https://arxiv.org/abs/1704.04861)

5.[MobileNets+SSD](https://ieeexplore.ieee.org/document/8099834/)
