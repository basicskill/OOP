add_library(Layer SHARED Layer.cpp)
add_library(LayerList SHARED LayerList.cpp Layer.cpp)
add_library(ImageEditor SHARED ImageEditor.cpp LayerList.cpp Layer.cpp)