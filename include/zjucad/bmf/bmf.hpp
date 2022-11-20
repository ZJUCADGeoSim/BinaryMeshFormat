#pragma once

#include <iostream>

#include <Eigen/Core>

namespace zjucad {
inline const char BMF_VERSION_MAJOR = 0;
inline const char BMF_VERSION_MINOR = 1;
using FLOAT = float;

void read_bmf(std::istream &fin,
              Eigen::MatrixX<FLOAT> &V,
              Eigen::MatrixX<FLOAT> &TC,
              Eigen::MatrixXi &F,
              Eigen::MatrixXi &FTC);

void write_bmf(std::ostream &fout,
               const Eigen::MatrixX<FLOAT> &V,
               const Eigen::MatrixX<FLOAT> &TC,
               const Eigen::MatrixXi &F,
               const Eigen::MatrixXi &FTC);

void read_bmf(const char *filename,
              Eigen::MatrixX<FLOAT> &V,
              Eigen::MatrixX<FLOAT> &TC,
              Eigen::MatrixXi &F,
              Eigen::MatrixXi &FTC);

void write_bmf(const char *filename,
               const Eigen::MatrixX<FLOAT> &V,
               const Eigen::MatrixX<FLOAT> &TC,
               const Eigen::MatrixXi &F,
               const Eigen::MatrixXi &FTC);
} // namespace zjucad