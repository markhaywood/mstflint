#include <map>

#include "signature_manager.h"
#include "flint_io.h"
#include "flint_base.h"
#include "fw_ops.h"
#include "fs3_ops.h"
#include "tools_utils.h"

using namespace std;


bool BluefieldFwOperationsSignatureManager::AddSignature(mfile* mf, Fs3Operations* imageOps, Flash *f, u_int32_t imageOffset)
{
(void)imageOffset;
#if !defined(UEFI_BUILD) && !defined(NO_OPEN_SSL)
    if (mf->tp == MST_SOFTWARE) {
        const unsigned int KEYLENGTH = 64;
        vector<u_int8_t> key;
        vector<u_int8_t> digest;

        //read the on-chip EFUSE value of MDK, MDK 512 bits are located at 0x1c1640-0x1c167c
        key.resize(KEYLENGTH);
        if (mread4_block(mf, 0x1c1640, (u_int32_t*)key.data(), KEYLENGTH) != (int)KEYLENGTH) {
            return errmsg("Failed to read MDK from CR");
        }

        if (!imageOps->CalcHMAC(key, digest)) {
            return false;
        }

        // burn the HMAC digest
        u_int32_t sectionSize = 0x0;
        u_int32_t sectionOffset = 0x0;
        if (!imageOps->GetSectionSizeAndOffset(FS3_HMAC, sectionSize, sectionOffset)) {
            return errmsg("Could not retrieve HMAC section size and offset");
        }

        size_t digestSizeInDW = digest.size() >> 2;
        u_int32_t* digestDWP = (u_int32_t*)digest.data();
        for (unsigned int i = 0; i < digestSizeInDW; i++) {
            digestDWP[i] = CPU_TO_BE32(digestDWP[i]);
        }
        if (!f->write(sectionOffset, digest.data(), sectionSize, true)) {
            return errmsg(MLXFW_FLASH_WRITE_ERR, "Failed to burn HMAC digest: %s", f->err());
        }
    }
#else
    (void)imageOps;
    (void)f;
    //ignore for UEFI
#endif
    return true;
};
