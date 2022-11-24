namespace cg2 {
    void clamping0_255(int &val) {
        if (val > 255) {
            val = 255;
        }
        if (val < 0) {
            val = 0;
        }
    }

    void clamping_minus128_127(int &val) {
        if (val  < -128) {
            val = -128;
        }

        if (val > 127) {
            val = 127;
        }
    }
}
