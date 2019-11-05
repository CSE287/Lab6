//
// Created by femianjc on 9/23/19.
//

#ifndef F_RAY_TRACE_PNM_HPP
#define F_RAY_TRACE_PNM_HPP

#include <numeric>
#include <cstdio>
#include <glm/glm.hpp>
#include <utility>
#include <valarray>
#include <string>

inline int clip(int x, int min=0, int max=255) {
    if (x < min){
        return min;
    } else if (x > max) {
        return max;
    } else {
        return x;
    }
}

template<typename T>
inline void save_ppm(char const* fname, T const *buf, int w, int h){
    FILE* fp = fopen(fname, "wb");
    fprintf(fp, "P6\n%d\n%d\n%d\n", w, h, 255);
    for (int i = 0; i < h; ++i){
        for (int j = 0; j < w; ++j) {
            for (int k = 0; k < 3; ++k){
                float v = *buf;
                fputc(clip(int(v * 255)), fp);
                ++buf;
            }
        }
    }
    fclose(fp);
}

template<typename T>
inline void save_ppm(std::string const& fname, T const* buf, int w, int h) {
    save_ppm(fname.c_str(), buf, w, h);
}


struct Image{
public:
    typedef glm::dvec3 Pixel;
private:
    int w;
    int h;
    std::valarray<Pixel> pix;
public:
    int width() const {return w;}
    int height() const {return h;}
    Pixel* operator[](int i) { return &pix[i*w];}
    Pixel const* operator[](int i) const {return &pix[i*w];}
    Image(int w=1, int h=1, Pixel const& fill=Pixel()): w(w), h(h), pix(fill,w*h) {}
    Image(int w, int h, std::valarray<Pixel>  data): w(w), h(h), pix(std::move(data)) {}

    Pixel const* begin() const { return std::begin(pix);}
    Pixel * begin() { return std::begin(pix);}
    Pixel * end() { return std::end(pix);}
    Pixel const * end() const { return std::end(pix);}

    bool compare(Image const& o, double atol=1/510.) const {
        if (w != o.w || h != o.h) { return false;}

        for (int i = 0; i < h; ++i){
            for (int j = 0; j < w; ++j){
                for (int k = 0; k < 3; ++k) {
                    if (abs((*this)[i][j][k] - o[i][j][k]) > atol) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    bool operator==(Image const& o) const { return compare(o);}

    Image& load(const std::string& path) {
        FILE *fp = fopen(path.c_str(), "rb");
        assert(fp);
        int cmax;
        fscanf(fp, "P6\n%d\n%d\n%d\n", &w, &h, &cmax);
        pix.resize(w*h);
        auto p = begin();
        for (int i = 0; i < h; ++i){
            for (int j = 0; j < w; ++j) {
                p->r = fgetc(fp)/255.;
                p->g = fgetc(fp)/255.;
                p->b = fgetc(fp)/255.;
                p++;
            }
        }
        fclose(fp);
        return *this;
    }

    void save(std::string const& path) {
        save_ppm(path, &pix[0][0], w, h);
    }
};

inline Image load_ppm(std::string const& path) {
    return Image().load(path);
}
#endif //F_RAY_TRACE_PNM_HPP
