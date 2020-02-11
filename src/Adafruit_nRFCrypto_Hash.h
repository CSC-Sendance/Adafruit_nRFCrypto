/* 
 * The MIT License (MIT)
 *
 * Copyright (c) 2020 Ha Thach (tinyusb.org) for Adafruit Industries
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef ADAFRUIT_NRFCRYPTO_HASH_H_
#define ADAFRUIT_NRFCRYPTO_HASH_H_

#include "nrf_cc310/include/crys_hash.h"

class Adafruit_nRFCrypto_Hash
{
  public:
    Adafruit_nRFCrypto_Hash(void);

    bool begin(CRYS_HASH_OperationMode_t mode);
    bool begin(uint32_t mode)
    {
      return begin ((CRYS_HASH_OperationMode_t) mode);
    }

    bool update(uint8_t data[], size_t size);

    uint8_t end(uint32_t result[16]);
    uint8_t end(uint8_t  result[64])
    {
      return end((uint32_t*) result);
    }

  private:
    CRYS_HASHUserContext_t _context;
    uint8_t _digest_len;
};

#endif /* ADAFRUIT_NRFCRYPTO_HASH_H_ */
