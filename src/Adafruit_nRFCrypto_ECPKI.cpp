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

#include "Adafruit_nRFCrypto.h"

#include "nrf_cc310/include/crys_ecpki_domain.h"
#include "nrf_cc310/include/crys_ecpki_kg.h"
#include "nrf_cc310/include/crys_ecpki_build.h"

//--------------------------------------------------------------------+
// MACRO TYPEDEF CONSTANT ENUM DECLARATION
//--------------------------------------------------------------------+


//------------- IMPLEMENTATION -------------//
Adafruit_nRFCrypto_ECC::Adafruit_nRFCrypto_ECC(void)
{
  _domain = NULL;
}

bool Adafruit_nRFCrypto_ECC::begin(CRYS_ECPKI_DomainID_t id)
{
  nRFCrypto.enable();

  _domain = CRYS_ECPKI_GetEcDomain(id);

  nRFCrypto.disable();
  return _domain != NULL;
}

void Adafruit_nRFCrypto_ECC::end(void)
{
  _domain = NULL;
}

bool Adafruit_nRFCrypto_ECC::genKeyPair(CRYS_ECPKI_UserPrivKey_t* private_key, CRYS_ECPKI_UserPublKey_t* public_key)
{
  CRYS_ECPKI_KG_TempData_t* tempbuf = (CRYS_ECPKI_KG_TempData_t*) rtos_malloc( sizeof(CRYS_ECPKI_KG_TempData_t) );
  VERIFY(tempbuf);

  nRFCrypto.enable();

  uint32_t err = CRYS_ECPKI_GenKeyPair(nRFCrypto.Random.getContext(), CRYS_RND_GenerateVector, _domain,
                                       private_key, public_key,
                                       tempbuf, NULL);

  nRFCrypto.disable();

  rtos_free(tempbuf);

  VERIFY_CRYS(err, false);
  return true;
}

// Export from internal type to raw bytes in Big Endian
// return raw buffer size = keysize + 1 (header)
uint32_t Adafruit_nRFCrypto_ECC::exportKey(CRYS_ECPKI_UserPublKey_t* pubkey, uint8_t* rawkey, uint32_t bufsize)
{
  nRFCrypto.enable();

  uint32_t err = CRYS_ECPKI_ExportPublKey(pubkey, CRYS_EC_PointUncompressed, rawkey, &bufsize);

  nRFCrypto.disable();

  VERIFY_CRYS(err, 0);
  return bufsize;
}

// Build public key from raw bytes in Big Endian
bool Adafruit_nRFCrypto_ECC::buildKey(CRYS_ECPKI_UserPublKey_t* pubkey, uint8_t* rawkey, uint32_t bufsize)
{
  CRYS_ECPKI_BUILD_TempData_t* tempbuf = (CRYS_ECPKI_BUILD_TempData_t*) rtos_malloc( sizeof(CRYS_ECPKI_BUILD_TempData_t) );
  VERIFY(tempbuf);

  nRFCrypto.enable();

  uint32_t err = CRYS_ECPKI_BuildPublKeyPartlyCheck(_domain, rawkey, bufsize, pubkey, tempbuf);

  nRFCrypto.disable();

  rtos_free(tempbuf);

  VERIFY_CRYS(err, false);
  return true;
}

