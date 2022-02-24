
#ifndef _MD5_ALGO_H_
#define _MD5_ALGO_H_

#include "../.././COMMON/Includes.h"

#define POLARSSL_ERR_MD5_FILE_IO_ERROR                 -0x0074  /**< Read/write error in file. */

/**
 * \brief          MD5 context structure
 */
typedef struct
{
	INT32U total[2];          /*!< number of bytes processed  */
	INT32U state[4];          /*!< intermediate digest state  */
    unsigned char buffer[64];   /*!< data block being processed */

    unsigned char ipad[64];     /*!< HMAC: inner padding        */
    unsigned char opad[64];     /*!< HMAC: outer padding        */
}
md5_context;

/**
 * \brief          Initialize MD5 context
 *
 * \param ctx      MD5 context to be initialized
 */
void md5_init( md5_context *ctx );

/**
 * \brief          Clear MD5 context
 *
 * \param ctx      MD5 context to be cleared
 */
void md5_free( md5_context *ctx );

/**
 * \brief          MD5 context setup
 *
 * \param ctx      context to be initialized
 */
void md5_starts( md5_context *ctx );

/**
 * \brief          MD5 process buffer
 *
 * \param ctx      MD5 context
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 */
void md5_update( md5_context *ctx, const unsigned char *input, SIZE_t ilen );

/**
 * \brief          MD5 final digest
 *
 * \param ctx      MD5 context
 * \param output   MD5 checksum result
 */
void md5_finish( md5_context *ctx, unsigned char output[16] );

/* Internal use */
void md5_process( md5_context *ctx, const unsigned char data[64] );

/**
 * \brief          Output = MD5( input buffer )
 *
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 * \param output   MD5 checksum result
 */
void md5( const unsigned char *input, SIZE_t ilen, unsigned char output[16] );

/**
 * \brief          Output = MD5( file contents )
 *
 * \param path     input file name
 * \param output   MD5 checksum result
 *
 * \return         0 if successful, or POLARSSL_ERR_MD5_FILE_IO_ERROR
 */
int md5_file( const char *path, unsigned char output[16] );

/**
 * \brief          MD5 HMAC context setup
 *
 * \param ctx      HMAC context to be initialized
 * \param key      HMAC secret key
 * \param keylen   length of the HMAC key
 */
void md5_hmac_starts( md5_context *ctx,
                      const unsigned char *key, SIZE_t keylen );

/**
 * \brief          MD5 HMAC process buffer
 *
 * \param ctx      HMAC context
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 */
void md5_hmac_update( md5_context *ctx,
                      const unsigned char *input, SIZE_t ilen );

/**
 * \brief          MD5 HMAC final digest
 *
 * \param ctx      HMAC context
 * \param output   MD5 HMAC checksum result
 */
void md5_hmac_finish( md5_context *ctx, unsigned char output[16] );

/**
 * \brief          MD5 HMAC context reset
 *
 * \param ctx      HMAC context to be reset
 */
void md5_hmac_reset( md5_context *ctx );

/**
 * \brief          Output = HMAC-MD5( hmac key, input buffer )
 *
 * \param key      HMAC secret key
 * \param keylen   length of the HMAC key
 * \param input    buffer holding the  data
 * \param ilen     length of the input data
 * \param output   HMAC-MD5 result
 */
void md5_hmac( const unsigned char *key, SIZE_t keylen,
               const unsigned char *input, SIZE_t ilen,
               unsigned char output[16] );

#endif /* md5.h */
