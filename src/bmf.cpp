#include <limits>
#include <zjucad/bmf/bmf.hpp>

#include <fstream>

namespace zjucad {

void read_bmf(std::istream &fin,
              Eigen::MatrixX<FLOAT> &V,
              Eigen::MatrixX<FLOAT> &TC,
              Eigen::MatrixXi &F,
              Eigen::MatrixXi &FTC) {
    char header[4];
    fin.read(header, 4);
    if (header[0] != 'b' && header[1] != 'm') {
        throw std::runtime_error("not a bmf file");
    }
    if (header[2] != BMF_VERSION_MAJOR || header[3] != BMF_VERSION_MINOR) {
        throw std::runtime_error("unsupported bmf version");
    }

    int n_vertices = 0, n_faces = 0, n_texture_vertices = 0, n_face_vert = 3;
    fin.read(reinterpret_cast<char *>(&n_vertices), sizeof(int));
    fin.read(reinterpret_cast<char *>(&n_texture_vertices), sizeof(int));
    fin.read(reinterpret_cast<char *>(&n_faces), sizeof(int));
    fin.read(reinterpret_cast<char *>(&n_face_vert), sizeof(int));

    V.resize(n_vertices, 3);
    fin.read(reinterpret_cast<char *>(V.data()), n_vertices * 3 * sizeof(FLOAT));

    if (n_texture_vertices > 0) {
        TC.resize(n_texture_vertices, 2);
        fin.read(reinterpret_cast<char *>(TC.data()), n_texture_vertices * 2 * sizeof(FLOAT));
    }

    if (n_vertices > std::numeric_limits<unsigned short>::max()) {
        F.resize(n_faces, n_face_vert);
        fin.read(reinterpret_cast<char *>(F.data()), n_faces * n_face_vert * sizeof(int));
    } else {
        Eigen::MatrixX<unsigned short> Fs;
        Fs.resize(n_faces, n_face_vert);
        fin.read(reinterpret_cast<char *>(Fs.data()), n_faces * n_face_vert * sizeof(unsigned short));
        F = Fs.cast<int>();
    }

    if (n_texture_vertices > 0) {
        if (n_texture_vertices > std::numeric_limits<unsigned short>::max()) {
            FTC.resize(n_faces, n_face_vert);
            fin.read(reinterpret_cast<char *>(FTC.data()), n_faces * n_face_vert * sizeof(int));
        } else {
            Eigen::MatrixX<unsigned short> FTCs;
            FTCs.resize(n_faces, n_face_vert);
            fin.read(reinterpret_cast<char *>(FTCs.data()), n_faces * n_face_vert * sizeof(unsigned short));
            FTC = FTCs.cast<int>();
        }
    }
}

void write_bmf(std::ostream &fout,
               const Eigen::MatrixX<FLOAT> &V,
               const Eigen::MatrixX<FLOAT> &TC,
               const Eigen::MatrixXi &F,
               const Eigen::MatrixXi &FTC) {
    char header[4] = {'b', 'm', BMF_VERSION_MAJOR, BMF_VERSION_MINOR};
    fout.write(header, 4);

    int n_vertices = V.rows(), n_faces = F.rows(), n_texture_vertices = TC.rows(), n_face_vert = F.cols();
    fout.write(reinterpret_cast<char *>(&n_vertices), sizeof(int));
    fout.write(reinterpret_cast<char *>(&n_texture_vertices), sizeof(int));
    fout.write(reinterpret_cast<char *>(&n_faces), sizeof(int));
    fout.write(reinterpret_cast<char *>(&n_face_vert), sizeof(int));

    fout.write(reinterpret_cast<const char *>(V.data()), n_vertices * 3 * sizeof(FLOAT));
    if (n_texture_vertices > 0) {
        fout.write(reinterpret_cast<const char *>(TC.data()), n_texture_vertices * 2 * sizeof(FLOAT));
    }
    if (n_vertices > std::numeric_limits<unsigned short>::max()) {
        fout.write(reinterpret_cast<const char *>(F.data()), n_faces * n_face_vert * sizeof(int));
    } else {
        Eigen::MatrixX<unsigned short> Fs = F.cast<unsigned short>();
        fout.write(reinterpret_cast<const char *>(Fs.data()), n_faces * n_face_vert * sizeof(unsigned short));
    }

    if (n_texture_vertices > 0) {
        if (n_texture_vertices > std::numeric_limits<unsigned short>::max()) {
            fout.write(reinterpret_cast<const char *>(FTC.data()), n_faces * n_face_vert * sizeof(int));
        } else {
            Eigen::MatrixX<unsigned short> FTCs = FTC.cast<unsigned short>();
            fout.write(reinterpret_cast<const char *>(FTCs.data()), n_faces * n_face_vert * sizeof(unsigned short));
        }
    }
}

void read_bmf(const char *filename,
              Eigen::MatrixX<FLOAT> &V,
              Eigen::MatrixX<FLOAT> &TC,
              Eigen::MatrixXi &F,
              Eigen::MatrixXi &FTC) {
    std::ifstream fin(filename, std::ios::binary);
    if (!fin) {
        throw std::invalid_argument("can not open file");
    }
    read_bmf(fin, V, TC, F, FTC);
}

void write_bmf(const char *filename,
               const Eigen::MatrixX<FLOAT> &V,
               const Eigen::MatrixX<FLOAT> &TC,
               const Eigen::MatrixXi &F,
               const Eigen::MatrixXi &FTC) {
    std::ofstream fout(filename, std::ios::binary | std::ios::trunc);
    if (!fout) {
        throw std::invalid_argument("can not open file");
    }
    write_bmf(fout, V, TC, F, FTC);
}
} // namespace zjucad