class FavorReg<string n> : Register<n> {
    let Namespace = "Favor";
}

class FavorGPR<bits<16> enc, string n> : Register<n> {
    let Namespace = "Favor";
    let HWEncoding = enc;
}

let Namespace = "Favor" in {
    def A0: FavorGPR<0, "a0">;
    def A1: FavorGPR<1, "a1">;
    def A2: FavorGPR<2, "a2">;
    def A3: FavorGPR<3, "a3">;

    def A4: FavorGPR<4, "a4">;
    def A5: FavorGPR<5, "a5">;
    def A6: FavorGPR<6, "a6">;
    def A7: FavorGPR<7, "a7">;

    def A8: FavorGPR<8, "a8">;
    def A9: FavorGPR<9, "a9">;
    def A10: FavorGPR<10, "a10">;
    def A11: FavorGPR<11, "a11">;

    def T0: FavorGPR<12, "t0">;
    def T1: FavorGPR<13, "t1">;
    def T2: FavorGPR<14, "t2">;
    def T3: FavorGPR<15, "t3">;

    def T4: FavorGPR<16, "t4">;
    def T5: FavorGPR<17, "t5">;
    def T6: FavorGPR<18, "t6">;
    def T7: FavorGPR<19, "t7">;

    def T8: FavorGPR<20, "t8">;
    def T9: FavorGPR<21, "t9">;
    def T10: FavorGPR<22, "t10">;
    def T11: FavorGPR<23, "t11">;

    def R0: FavorGPR<24, "r0">;
    def R1: FavorGPR<25, "r1">;
    def R2: FavorGPR<26, "r2">;
    def R3: FavorGPR<27, "r3">;

    def FP: FavorGPR<28, "fp">;
    def LA: FavorGPR<29, "la">;
    def SP: FavorGPR<30, "sp">;
    def ZERO: FavorGPR<31, "zero"> {
        let isConstant = 1;
    }
}

def GPR64: RegisterClass<"Favor",
    [i8, i16, i32, i64],
    64,
    (add
        // Argument registers
        A0, A1, A2, A3,
        A4, A5, A6, A7,
        A8, A9, A10, A11,
        // Temporary registers
        T0, T1, T2, T3,
        T4, T5, T6, T7,
        T8, T9, T10, T11,
        // Temporary R registers
        R0, R1, R2, R3,
        // Frame pointer
        FP,
        // Link address
        LA,
        // Stack pointer
        SP,
        // Zero register
        ZERO
    )>;
def GPR64ZERO: RegisterClass<"Favor",
    [i8, i16, i32, i64],
    64,
    (add ZERO)>;
def GPR64NONZERO: RegisterClass<"Favor",
    [i8, i16, i32, i64],
    64,
    (sub GPR64, GPR64ZERO)>;

let isAllocatable = false in {
    def CPULAREG : RegisterClass<"Favor",
        [i8, i16, i32, i64], 64, (add LA)>;
    def CPUSPREG : RegisterClass<"Favor",
        [i8, i16, i32, i64], 64, (add SP)>;
}