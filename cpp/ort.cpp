#include <onnxruntime/onnxruntime_cxx_api.h>

int main() {
  Ort::SessionOptions session_options;

  // Set graph optimization level
  session_options.SetGraphOptimizationLevel(
      GraphOptimizationLevel::ORT_ENABLE_ALL);

  // To enable model serialization after graph optimization set this
  session_options.SetOptimizedModelFilePath("ssdmnv2optimized.onnx");

  Ort::Env env;
  auto session_ = Ort::Session(env, "onnx/ssd/ssd_mobilenet_v2_fpnlite_640x640_coco17_tpu-8/model.onnx", session_options);
}
