#pragma once
#include <torch/torch.h>
#include <torch/types.h>
#include <torch/data/example.h>
#include <torch/data/datasets/base.h>
#include "bounding_box.h"
#include "coco.h"


namespace rcnn{
namespace data{

struct RCNNData{
  int64_t idx;
  rcnn::structures::BoxList target;
};

class COCODetection : public torch::data::datasets::Dataset<COCODetection, torch::data::Example<torch::Tensor, std::vector<coco::Annotation>>> {

public:
  COCODetection(std::string root, std::string annFile/*TODO transform=*/);
  torch::data::Example<torch::Tensor, std::vector<coco::Annotation>> get(size_t index) override;
  torch::optional<size_t> size() const override;

private:
  std::string root_;
  coco::COCO coco_;
  std::vector<int64_t> ids_;

friend std::ostream& operator << (std::ostream& os, const COCODetection& bml);
};



}//data
}//rcnn

