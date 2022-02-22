CPMAddPackage(
    NAME cryptopp
    VERSION 8.6
    URL https://github.com/weidai11/cryptopp/archive/refs/tags/CRYPTOPP_8_6_0.zip
    DOWNLOAD_ONLY YES
)

if (cryptopp_ADDED)

    option(CRYPTOPP_DISABLE_ASM "Disable ASM" ON)
    option(CRYPTOPP_DISABLE_SSSE3 "Disable SSSE3" ON)
    option(CRYPTOPP_DISABLE_AESNI "Disable AES-NI" ON)

    set(cryptopp_SOURCES
        #3way.cpp
        #adler32.cpp
        algebra.cpp
        algparam.cpp
        allocate.cpp
        # arc4.cpp
        # aria.cpp
        # aria_simd.cpp
        # ariatab.cpp
        # asn.cpp
         authenc.cpp
         base32.cpp
         base64.cpp
        # basecode.cpp
        # bench1.cpp
        # bench2.cpp
        # bench3.cpp
        #bfinit.cpp
        #blake2b_simd.cpp
        #blake2.cpp
        #blake2s_simd.cpp
        #blowfish.cpp
        #blumshub.cpp
        #camellia.cpp
        #cast.cpp
        #casts.cpp
        #cbcmac.cpp
        #ccm.cpp
        #chacha_avx.cpp
        #chacha.cpp
        #chachapoly.cpp
        #chacha_simd.cpp
        #cham.cpp
        #cham_simd.cpp
        #channels.cpp
        #cmac.cpp
        #cpu.cpp
        #crc.cpp
        #crc_simd.cpp
         cryptlib.cpp
        #darn.cpp
        # datatest.cpp
        default.cpp
        # des.cpp
        # dessp.cpp
        # dh2.cpp
        # dh.cpp
        # dll.cpp
        # dlltest.cpp
        # donna_32.cpp
        # donna_64.cpp
        # donna_sse.cpp
        # dsa.cpp
        # eax.cpp
        # ec2n.cpp
        # eccrypto.cpp
        # ecp.cpp
        # elgamal.cpp
        # emsa2.cpp
        # eprecomp.cpp
        # esign.cpp
        # files.cpp
         filters.cpp
        # fips140.cpp
        # fipsalgt.cpp
        # fipstest.cpp
        #gcm.cpp
        #gcm_simd.cpp
        #gf2_32.cpp
        #gf256.cpp
        #gf2n.cpp
        #gf2n_simd.cpp
        #gfpcrypt.cpp
        #gost.cpp
        #gzip.cpp
        #hc128.cpp
        #hc256.cpp
        #hex.cpp
        #hight.cpp
        #hmac.cpp
        #hrtimer.cpp
        #ida.cpp
        #idea.cpp
        integer.cpp
        iterhash.cpp
        # kalyna.cpp
        # kalynatab.cpp
        # keccak_core.cpp
        # keccak.cpp
        # keccak_simd.cpp
        # lea.cpp
        # lea_simd.cpp
        # lsh256_avx.cpp
        # lsh256.cpp
        # lsh256_sse.cpp
        # lsh512_avx.cpp
        # lsh512.cpp
        # lsh512_sse.cpp
        # luc.cpp
        # mars.cpp
        # marss.cpp
        # md2.cpp
        # md4.cpp
        # md5.cpp
        # misc.cpp
        # modes.cpp
        # mqueue.cpp
        # mqv.cpp
        # nbtheory.cpp
        # neon_simd.cpp
        # oaep.cpp
        osrng.cpp
        #padlkrng.cpp
        panama.cpp
        #pch.cpp
        #pkcspad.cpp
        #poly1305.cpp
        #polynomi.cpp
        #ppc_power7.cpp
        #ppc_power8.cpp
        #ppc_power9.cpp
        #ppc_simd.cpp
        #pssr.cpp
        #pubkey.cpp
        #queue.cpp
        #rabbit.cpp
        #rabin.cpp
        randpool.cpp
        # rc2.cpp
        # rc5.cpp
        # rc6.cpp
        # rdrand.cpp
        # rdtables.cpp
        # regtest1.cpp
        # regtest2.cpp
        # regtest3.cpp
        # regtest4.cpp
        #rijndael.cpp
        #rijndael_simd.cpp
        # ripemd.cpp
        rng.cpp
        # rsa.cpp
        # rw.cpp
        # safer.cpp
        # salsa.cpp
        # scrypt.cpp
        # seal.cpp
        # seed.cpp
        # serpent.cpp
         sha3.cpp
        # shacal2.cpp
        # shacal2_simd.cpp
         sha.cpp
        # shake.cpp
        # sharkbox.cpp
        # shark.cpp
        # sha_simd.cpp
        # simeck.cpp
        # simon128_simd.cpp
        # simon.cpp
        # simple.cpp
        # skipjack.cpp
        # sm3.cpp
        # sm4.cpp
        # sm4_simd.cpp
        # sosemanuk.cpp
        # speck128_simd.cpp
        # speck.cpp
        # square.cpp
        # squaretb.cpp
        # sse_simd.cpp
         strciphr.cpp
        # tea.cpp
        # test.cpp
        # tftables.cpp
        # threefish.cpp
        # tiger.cpp
        # tigertab.cpp
        # ttmac.cpp
        # tweetnacl.cpp
        # twofish.cpp
        # validat0.cpp
        # validat10.cpp
        # validat1.cpp
        # validat2.cpp
        # validat3.cpp
        # validat4.cpp
        # validat5.cpp
        # validat6.cpp
        # validat7.cpp
        # validat8.cpp
        # validat9.cpp
        # vmac.cpp
        # wake.cpp
        # whrlpool.cpp
        # xed25519.cpp
        # xtr.cpp
        # xtrcrypt.cpp
        # xts.cpp
        # zdeflate.cpp
        # zinflate.cpp
        # zlib.cpp
        )

    set(cryptopp_HEADERS
        #3way.h
        adler32.h
        adv_simd.h
        aes_armv4.h
        aes.h
        algebra.h
        algparam.h
        allocate.h
        # arc4.h
        # argnames.h
        # aria.h
        # arm_simd.h
        # asn.h
        authenc.h
        base32.h
        base64.h
        basecode.h
        # bench.h
        # blake2.h
        # blowfish.h
        # blumshub.h
        # camellia.h
        # cast.h
        # cbcmac.h
        # ccm.h
        # chacha.h
        # chachapoly.h
        # cham.h
        # channels.h
        # cmac.h
        # config_align.h
        # config_asm.h
        # config_cpu.h
        # config_cxx.h
        # config_dll.h
        # config.h
        # config_int.h
        # config_misc.h
        # config_ns.h
        # config_os.h
        # config_ver.h
         cpu.h
        # crc.h
        cryptlib.h
        # darn.h
        # default.h
        # des.h
        # dh2.h
        # dh.h
        # dll.h
        # dmac.h
        # donna_32.h
        # donna_64.h
        # donna.h
        # donna_sse.h
        # drbg.h
        # dsa.h
        # eax.h
        # ec2n.h
        # eccrypto.h
        # ecp.h
        # ecpoint.h
        # elgamal.h
        # emsa2.h
        # eprecomp.h
        # esign.h
        # factory.h
        # fhmqv.h
        # files.h
         filters.h
        # fips140.h
        # fltrimpl.h
        # gcm.h
        # gf2_32.h
        # gf256.h
        # gf2n.h
        # gfpcrypt.h
        # gost.h
        # gzip.h
        # hashfwd.h
        # hc128.h
        # hc256.h
        # hex.h
        # hight.h
        # hkdf.h
        # hmac.h
        # hmqv.h
        # hrtimer.h
        # ida.h
        # idea.h
          integer.h
         iterhash.h
        # kalyna.h
        # keccak.h
        # lea.h
        # lsh.h
        # lubyrack.h
        # luc.h
        # mars.h
        # md2.h
        # md4.h
        # md5.h
        # mdc.h
        # mersenne.h
        # misc.h
        # modarith.h
        # modes.h
        # modexppc.h
        # mqueue.h
        # mqv.h
        # naclite.h
        # nbtheory.h
        # nr.h
        # oaep.h
        # oids.h
         osrng.h
        # ossig.h
        # padlkrng.h
        # panama.h
        # pch.h
        # pkcspad.h
        # poly1305.h
        # polynomi.h
        # ppc_simd.h
        # pssr.h
        # pubkey.h
        pwdbased.h
        queue.h
        # rabbit.h
        # rabin.h
         randpool.h
        # rc2.h
        # rc5.h
        # rc6.h
         rdrand.h
        # resource.h
        # rijndael.h
        # ripemd.h
        rng.h
        # rsa.h
        # rw.h
        # safer.h
        # salsa.h
         scrypt.h
        # seal.h
        # secblockfwd.h
        # secblock.h
        # seckey.h
        # seed.h
        # serpent.h
        # serpentp.h
        # sha1_armv4.h
         sha256_armv4.h
        # sha3.h
        # sha512_armv4.h
        # shacal2.h
         sha.h
        # shake.h
        # shark.h
        # simeck.h
        # simon.h
        # simple.h
        # siphash.h
        # skipjack.h
        # sm3.h
        # sm4.h
         smartptr.h
        # sosemanuk.h
        # speck.h
        # square.h
        # stdcpp.h
         strciphr.h
        # tea.h
        # threefish.h
        # tiger.h
         trap.h
        # trunhash.h
        # ttmac.h
        # tweetnacl.h
        # twofish.h
        # validate.h
        # vmac.h
        # wake.h
        # whrlpool.h
        # words.h
        # xed25519.h
        # xtrcrypt.h
        # xtr.h
        # xts.h
        # zdeflate.h
        # zinflate.h
        # zlib.h
        )

    # Set flags
    IF (CRYPTOPP_DISABLE_ASM)
        ADD_DEFINITIONS (-DCRYPTOPP_DISABLE_ASM)
    ENDIF ()
    IF (CRYPTOPP_DISABLE_SSSE3)
        ADD_DEFINITIONS (-DCRYPTOPP_DISABLE_SSSE3)
    ENDIF ()
    IF (CRYPTOPP_DISABLE_AESNI)
        ADD_DEFINITIONS (-DCRYPTOPP_DISABLE_AESNI)
    ENDIF ()

    list(TRANSFORM cryptopp_SOURCES PREPEND ${cryptopp_SOURCE_DIR}/)
    list(TRANSFORM cryptopp_HEADERS PREPEND ${cryptopp_SOURCE_DIR}/)

    add_library(cryptopp-shared ${cryptopp_SOURCES} ${cryptopp_HEADERS})
    target_include_directories(cryptopp-shared PUBLIC $<BUILD_INTERFACE:${cryptopp_SOURCE_DIR}>)

endif()
