class FavorReg<string n> : Register<n> {
    let Namespace = "Favor";
}

class FavorGPR<string n> : Register<n> {
    let Namespace = "Favor";
}

let Namespace = "Favor" in {
    def A0: FavorGPR<"a0">;
    def A1: FavorGPR<"a1">;
    def A2: FavorGPR<"a2">;
    def A3: FavorGPR<"a3">;

    def A4: FavorGPR<"a4">;
    def A5: FavorGPR<"a5">;
    def A6: FavorGPR<"a6">;
    def A7: FavorGPR<"a7">;

    def A8: FavorGPR<"a8">;
    def A9: FavorGPR<"a9">;
    def A10: FavorGPR<"a10">;
    def A11: FavorGPR<"a11">;

    def T0: FavorGPR<"t0">;
    def T1: FavorGPR<"t1">;
    def T2: FavorGPR<"t2">;
    def T3: FavorGPR<"t3">;

    def T4: FavorGPR<"t4">;
    def T5: FavorGPR<"t5">;
    def T6: FavorGPR<"t6">;
    def T7: FavorGPR<"t7">;

    def R0: FavorGPR<"r0">;
    def R1: FavorGPR<"r1">;
    def R2: FavorGPR<"r2">;
    def R3: FavorGPR<"r3">;

    def FP: FavorGPR<"fp">;
    def LA: FavorGPR<"la">;
    def SP: FavorGPR<"sp">;
    def ZERO: FavorGPR<"zero"> {
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