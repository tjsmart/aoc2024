typedef struct {
    int x;
    int y;
} slh_vec2_t;

slh_vec2_t slh_vec2_add(slh_vec2_t l, slh_vec2_t r) {
    return (slh_vec2_t){.x = l.x + r.x, .y = l.y + r.y};
}

slh_vec2_t slh_vec2_rotate(slh_vec2_t vec) {
    return (slh_vec2_t){.x = -vec.y, .y = vec.x};
}

bool slh_vec2_eq(slh_vec2_t l, slh_vec2_t r) {
    return l.x == r.x && l.y == r.y;
}
