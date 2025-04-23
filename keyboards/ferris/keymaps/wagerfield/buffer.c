// clang-format off
#include "buffer.h"

void buffer_init(keyrecord_buffer_t *buffer) {
    buffer_clear(buffer);
}

void buffer_clear(keyrecord_buffer_t *buffer) {
    buffer->head = 0;
    buffer->tail = 0;
    buffer->size = 0;
}

uint8_t buffer_get_size(keyrecord_buffer_t *buffer) {
    return buffer->size;
}

uint8_t buffer_get_capacity(void) {
    return KEYRECORD_BUFFER_SIZE;
}

bool buffer_is_empty(keyrecord_buffer_t *buffer) {
    return buffer->size == 0;
}

bool buffer_is_full(keyrecord_buffer_t *buffer) {
    return buffer->size == KEYRECORD_BUFFER_SIZE;
}

bool buffer_enqueue(keyrecord_buffer_t *buffer, keyrecord_t record) {
    if (buffer_is_full(buffer)) return false;
    buffer->records[buffer->head] = record;
    buffer->head = (buffer->head + 1) % KEYRECORD_BUFFER_SIZE;
    buffer->size++;
    return true;
}

bool buffer_dequeue(keyrecord_buffer_t *buffer, keyrecord_t *record) {
    if (buffer_is_empty(buffer)) return false;
    *record = buffer->records[buffer->tail];
    buffer->tail = (buffer->tail + 1) % KEYRECORD_BUFFER_SIZE;
    buffer->size--;
    return true;
}

bool buffer_peek(keyrecord_buffer_t *buffer, keyrecord_t *record) {
    if (buffer_is_empty(buffer)) return false;
    *record = buffer->records[buffer->tail];
    return true;
}

bool buffer_peek_at(keyrecord_buffer_t *buffer, keyrecord_t *record, uint8_t index) {
    if (index >= buffer->size) return false;
    // Calculate actual array index using modulo to handle buffer wrap-around
    uint8_t actual_index = (buffer->tail + index) % KEYRECORD_BUFFER_SIZE;
    *record = buffer->records[actual_index];
    return true;
}
