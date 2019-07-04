# maskrcnn_benchmark.cpp
faster rcnn cpp implementation based on maskrcnn-benchmark

# Codes
All code architecture from [maskrcnn-benchmark](https://github.com/facebookresearch/maskrcnn-benchmark)

# Installation
```
export INSTALL_DIR=$PWD
git clone --recursive https://github.com/lsrock1/maskrcnn_benchmark.cpp.git
cd $INSTALL_DIR

//opencv install
//ABI=0 is really important
cd maskrcnn_benchmark.cpp/lib/opencv
mkdir build
cd build
cmake -DCMAKE_CXX_FLAGS=-D_GLIBCXX_USE_CXX11_ABI=0 ..
make install

//yaml-cpp install
//ABI=0 is really important
cd $INSTALL_DIR
cd maskrcnn_benchmark.cpp/lib/yaml-cpp
mkdir build
cd build
cmake -DCMAKE_CXX_FLAGS=-D_GLIBCXX_USE_CXX11_ABI=0 ..
make install

//Download pytorch cpp
//place libtorch folder in lib directory
//if you are using without cuda and get dyld: Library not loaded: @rpath/libmklml.dylib error
//https://github.com/pytorch/pytorch/issues/14165

//fix libtorch bug
//https://github.com/pytorch/pytorch/pull/21134
//in maskrcnn_benchmark.cpp/lib/libtorch/include/torch/csrc/autograd/VariableTypeUtils.h
//insert #pramga once into the first line

cd $INSTALL_DIR
cd maskrcnn_benchmark.cpp
mkdir build
cd build
cmake ..
make

//run inference r50-fpn
./tmp.out

```

# Datasets
Download coco datasets  
make directory under maskrcnn_benchmark.cpp
```
datasets
  - coco
    - train2017
    - val2017
  - annotations
    - instances_val2017.json
    - instances_train2017.json
```

# Results

#### Under RTX2080ti 1 GPU, cuda 10, cudnn 7  
#### [ResNet](https://arxiv.org/abs/1512.03385)
#### [VoVNet](https://arxiv.org/abs/1904.09730)

backbone | type | lr sched | inference total batch | inference time(s/im) | box AP
-- | -- | -- | -- | -- | --
R-50-FPN(python) | Fast | 1x | 8 | 0.05989 | 0.368
R-50-FPN(cpp) | Fast | 1x | 8 | 0.05296 | 0.368
R-101-FPN(python) | Fast | 1x | 8 | 0.07627 | 0.391
R-101-FPN(cpp) | Fast | 1x | 8 | 0.07176 | 0.391
VoV-39(python) | Fast | 1x | 8 |  |
VoV-39(cpp) | Fast | 1x | 8 |  |
VoV-57(python) | Fast | 1x | 8 |  |
VoV-57(cpp) | Fast | 1x | 8 |  |

# Warning
### In Progress.  
* It doesn't support multi dataset training(like coco2014 with coco2014valminusminival, use coco2017 instead)
* It doesn't support training yet.(only support single gpu training but not tested).  
* It only tested in pre-trained model from python maskrcnn-benchmark.  
* It doesn't import evaluation process  

# TODO
- [ ] concat dataset
- [ ] Other model test
- [ ] python jit -> cpp model code
- [ ] Multi GPU training
- [ ] installable
- [ ] clean up code

# Requirements
Yaml-cpp
gtest
libtorch
rapidjson
opencv

# MODELS
Download into /models 

backbone | from | link 
-- | -- | -- 
R-50(backbone only) | python-pretrained | [link](https://www.dropbox.com/s/2q808v0p2j75lfq/resnet50_cpp.pth?dl=0)
R-101(backbone only) | python-pretrained | [link](https://www.dropbox.com/s/h5a51ur3qvrdjh5/resnet101_cpp.pth?dl=0)
R-50-FPN | python-trained | [link](https://www.dropbox.com/s/o889pmhzu2jxczl/frcn_r50_cpp.pth?dl=0)
R-101-FPN | python-trained | [link](https://www.dropbox.com/s/sgo3k502kegmcxa/frcn_r101_fpn_cpp.pth?dl=0)
R-50-C4 | python-trained | [link](https://www.dropbox.com/s/zu1yzt9ydlnqin4/frcn_r50_c4_cpp.pth?dl=0)
