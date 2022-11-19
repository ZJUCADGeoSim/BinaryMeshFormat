#pragma once

#include <iostream>

#include <Eigen/Core>

namespace zjucad {
inline const char BMF_VERSION_MAJOR = 0;
inline const char BMF_VERSION_MINOR = 1;

void read_bmf(std::istream &fin,
              Eigen::MatrixXd &V,
              Eigen::MatrixXd &TC,
              Eigen::MatrixXi &F,
              Eigen::MatrixXi &FTC);

void write_bmf(std::ostream &fout,
               const Eigen::MatrixXd &V,
               const Eigen::MatrixXd &TC,
               const Eigen::MatrixXi &F,
               const Eigen::MatrixXi &FTC);

void read_bmf(const char *filename,
              Eigen::MatrixXd &V,
              Eigen::MatrixXd &TC,
              Eigen::MatrixXi &F,
              Eigen::MatrixXi &FTC);

void write_bmf(const char *filename,
               const Eigen::MatrixXd &V,
               const Eigen::MatrixXd &TC,
               const Eigen::MatrixXi &F,
               const Eigen::MatrixXi &FTC);
} // namespace zjucad