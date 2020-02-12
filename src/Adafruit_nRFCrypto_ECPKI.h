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

#ifndef ADAFRUIT_NRFCRYPTO_ECPKI_H_
#define ADAFRUIT_NRFCRYPTO_ECPKI_H_

#include "nrf_cc310/include/crys_ecpki_types.h"
#include "nrf_cc310/include/crys_ecpki_error.h"

class Adafruit_nRFCrypto_ECC
{
  public:
    Adafruit_nRFCrypto_ECC(void);

    bool begin(CRYS_ECPKI_DomainID_t id);
    void end(void);

    bool genKeyPair(CRYS_ECPKI_UserPrivKey_t* private_key, CRYS_ECPKI_UserPublKey_t* public_key);

    uint32_t exportKey(CRYS_ECPKI_UserPublKey_t* pubkey, uint8_t* rawkey, uint32_t bufsize);
    bool buildKey(CRYS_ECPKI_UserPublKey_t* pubkey, uint8_t* rawkey, uint32_t bufsize);

  private:
    const CRYS_ECPKI_Domain_t * _domain;
};

#endif /* ADAFRUIT_NRFCRYPTO_ECPKI_H_ */
