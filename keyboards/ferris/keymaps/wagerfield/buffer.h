// clang-format off
#pragma once

#include "action.h"

#ifndef KEYRECORD_BUFFER_SIZE
#define KEYRECORD_BUFFER_SIZE 8
#endif

typedef struct {
    keyrecord_t records[KEYRECORD_BUFFER_SIZE];
    uint8_t head; // Points to the next free slot
    uint8_t tail; // Points to the oldest element
    uint8_t size; // Current number of elements
} keyrecord_buffer_t;

/**
 * @brief Initialize the buffer
 *
 * @param buffer Pointer to the keyrecord buffer to initialize
 */
void buffer_init(keyrecord_buffer_t *buffer);

/**
 * @brief Clear the buffer
 *
 * @param buffer Pointer to the keyrecord buffer to clear
 */
void buffer_clear(keyrecord_buffer_t *buffer);

/**
 * @brief Get the number of elements in the buffer
 *
 * @param buffer Pointer to the keyrecord buffer
 * @return Current size of the buffer
 */
uint8_t buffer_get_size(keyrecord_buffer_t *buffer);

/**
 * @brief Get the capacity of the buffer
 *
 * @return Total capacity of the buffer
 */
uint8_t buffer_get_capacity(void);

/**
 * @brief Check if buffer is empty
 *
 * @param buffer Pointer to the keyrecord buffer
 * @return true if buffer is empty, false otherwise
 */
bool buffer_is_empty(keyrecord_buffer_t *buffer);

/**
 * @brief Check if buffer is full
 *
 * @param buffer Pointer to the keyrecord buffer
 * @return true if buffer is full, false otherwise
 */
bool buffer_is_full(keyrecord_buffer_t *buffer);

/**
 * @brief Add a keyrecord to the buffer
 *
 * @param buffer Pointer to the keyrecord buffer
 * @param record The keyrecord to add
 * @return true if successful, false if buffer is full
 */
bool buffer_enqueue(keyrecord_buffer_t *buffer, keyrecord_t record);

/**
 * @brief Remove and return the oldest keyrecord from the buffer
 *
 * @param buffer Pointer to the keyrecord buffer
 * @param record Pointer where the retrieved keyrecord will be stored
 * @return true if successful, false if buffer is empty
 */
bool buffer_dequeue(keyrecord_buffer_t *buffer, keyrecord_t *record);

/**
 * @brief Look at the oldest keyrecord without removing it
 *
 * @param buffer Pointer to the keyrecord buffer
 * @param record Pointer where the peeked keyrecord will be stored
 * @return true if successful, false if buffer is empty
 */
bool buffer_peek(keyrecord_buffer_t *buffer, keyrecord_t *record);

/**
 * @brief Look at the nth keyrecord without removing it
 *
 * @param buffer Pointer to the keyrecord buffer
 * @param record Pointer where the peeked keyrecord will be stored
 * @param index Index to peek at (0 = oldest/tail, size-1 = newest/head-1)
 * @return true if successful, false if index is out of bounds
 */
bool buffer_peek_at(keyrecord_buffer_t *buffer, keyrecord_t *record, uint8_t index);
