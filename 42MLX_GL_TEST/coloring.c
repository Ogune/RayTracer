#include "header.h"

// Color manipulation functions
uint32_t get_rgba(uint32_t r, uint32_t g, uint32_t b, uint32_t a)
{
    return (r << 24) | (g << 16) | (b << 8) | a;
}

uint32_t get_r(uint32_t rgba) { return ((rgba >> 24) & 0xFF); }
uint32_t get_g(uint32_t rgba) { return ((rgba >> 16) & 0xFF); }
uint32_t get_b(uint32_t rgba) { return ((rgba >> 8) & 0xFF); }
uint32_t get_a(uint32_t rgba) { return (rgba & 0xFF); }

uint32_t createColor(float r, float g, float b, float a)
{
    uint32_t r_ = (uint32_t)(r * 255.0f);
    uint32_t g_ = (uint32_t)(g * 255.0f);
    uint32_t b_ = (uint32_t)(b * 255.0f);
    uint32_t a_ = (uint32_t)(a * 255.0f);
    return get_rgba(r_, g_, b_, a_);
}
