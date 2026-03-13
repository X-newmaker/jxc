#ifndef MODULE_CANFD_CAN_H_
#define MODULE_CANFD_CAN_H_



#define CANFD_0                                        0x000                                                                                           /* CANFD controller 0 */
#define CANFD_1                                        0x001                                                                                           /* CANFD controller 1 */
#define CANFD_LAST                                     CANFD_1

#define CANFD_SEL_MASK                                 0x1
#define CANFD_SEL(n)                                   (n & CANFD_SEL_MASK)

#define CANFD_RBUF(n)                                  (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x000)
#define CANFD_RUBF_OFFSET                              0x000                                                                                           /* Receive Buffer Registers 0x00-0x4f */
#define CANFD_RUBF_ID_OFFSET                           0x000                                                                                           /* Receive Buffer ID Registers */
#define CANFD_RBUF_CTL_OFFSET                          0x004                                                                                           /* Receive Buffer Control Registers */
#define CANFD_RBUF_IDE_SHIFT                           0x007                                                                                           /* Receive Buffer IDE bit shift */
#define CANFD_RBUF_RTR_SHIFT                           0x006                                                                                           /* Receive Buffer RTR bit shift */
#define CANFD_RBUF_FDF_SHIFT                           0x005                                                                                           /* Receive Buffer FDF bit shift */
#define CANFD_RBUF_BRS_SHIFT                           0x004                                                                                           /* Receive Buffer BRS bit shift */
#define CANFD_RBUF_DLC_SHIFT                           0x000                                                                                           /* Receive Buffer DLC field shift */
#define CANFD_RBUF_DATA_OFFSET                         0x008                                                                                           /* Receive Buffer DATA offset */

#define CANFD_TBUF(n)                                  (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x050)                    /* Transmit Buffer Registers 0x50-0x97 */

#define CANFD_TBUF_OFFSET                              0x050                                                                                           /* Transmit Buffer Registers 0x50-0x97 */
#define CANFD_TBUF_ID_OFFSET                           0x050                                                                                           /* Transmit Buffer ID Registers */
#define CANFD_TBUF_CTL_OFFSET                          0x054                                                                                           /* Transmit Buffer Control Registers */
#define CANFD_TBUF_DATA_OFFSET                         0x058                                                                                           /* Transmit Buffer DATA Registers */

#define CANFD_TTS(n)                                   (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x098)                    /* Transmission Time Stamp 0x98-0x9f */

#define CANFD_CFG(n)                                   (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0A0)

#define CANFD_SET_RST_MASK                             0x080                                                                                           /* Set Reset Bit */
#define CANFD_LBMEMOD_MASK                             0x040                                                                                           /* set loop back mode, external */
#define CANFD_LBMIMOD_MASK                             0x020                                                                                           /* set loop back mode, internal */
#define CANFD_TPSS_MASK                                0x010                                                                                           /* single shot mode for PTB */
#define CANFD_TSSS_MASK                                0x008                                                                                           /* single shot mode for STB */
#define CANFD_RASCTIVE_MASK                            0x004                                                                                           /* state of receiving a frame */
#define CANFD_TASCTIVE_MASK                            0x002                                                                                           /* state of transmitting a frame */
#define CANFD_SET_BUSOFF_MASK                          0x001                                                                                           /* bus off */

#define CANFD_TCMD(n)                                  (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0A1)

#define CANFD_SET_TBSEL_MASK                           0x080                                                                                           /* message writen in STB */
#define CANFD_SET_LOM_MASK                             0x040                                                                                           /* listen only mode enable */
#define CANFD_SET_STBY_MASK                            0x020                                                                                           /* transceiver standby mode */
#define CANFD_SET_TPE_MASK                             0x010                                                                                           /* Transmit primary enable */
#define CANFD_SET_TPA_MASK                             0x008                                                                                           /* Transmit primary abort */
#define CANFD_SET_TSONE_MASK                           0x004                                                                                           /* Transmit secondary one frame */
#define CANFD_SET_TSALL_MASK                           0x002                                                                                           /* Transmit secondary all frames */
#define CANFD_SET_TSA_MASK                             0x001                                                                                           /* Transmit secondary abort */

#define CANFD_TCTRL(n)                                 (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0A2)

#define CANFD_SET_ISO_CAN_MASK                         0x080                                                                                           /* select ISO CAN FD mode */
#define CANFD_SET_TENEXT_MASK                          0x040                                                                                           /* transmit buffer secondary next slot */
#define CANFD_PRIORITY_MASK                            0x020                                                                                           /* set TSMODE as 1->Priority mode */
#define CANFD_SET_FULLCAN_MASK                         0x010                                                                                           /* set TTTBM as 1->full TTCAN mode */
#define CANFD_TSSTAT_MASK                              0x003                                                                                           /* transmission secondary STATus bits */
#define CANFD_TSSTAT_EMP                               0x000                                                                                           /* transmission secondary STATus empty */
#define CANFD_TSSTAT_LESS_EQU_HALF                     0x001                                                                                           /* transmission secondary STATus less or equal to half */

#define CANFD_TSSTAT_NOTEMPTY_NOTFULL                  0x001                                                                                           /* transmission secondary STATus not empty and not full */
#define CANFD_TSSTAT_MORE_HALF                         0x002                                                                                           /* transmission secondary STATus more than half */
#define CANFD_TSSTAT_FULL                              0x003                                                                                           /* transmission secondary STATus full */

#define CANFD_RCTRL(n)                                 (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0A3)

#define CANFD_SACK_MASK                                0x080                                                                                           /* self-acknowledge */
#define CANFD_ROM_MASK                                 0x040                                                                                           /* receive buffer overflow mode */
#define CANFD_ROV_MASK                                 0x020                                                                                           /* receive buffer overflow */
#define CANFD_RREL_MASK                                0x010                                                                                           /* receive buffer release */
#define CANFD_RBALL_MASK                               0x008                                                                                           /* receive buffer stores all data frame */
#define CANFD_RSTAT_MASK                               0x003                                                                                           /* receive buffer status */
#define CANFD_RSTAT_EMP                                0x000                                                                                           /* receive buffer status: empty */
#define CANFD_RSTAT_SOME                               0x001                                                                                           /* receive buffer status: between empty and almost full */
#define CANFD_RSTAT_ALMOSTFULL                         0x002                                                                                           /* receive buffer status: almost full */
#define CANFD_RSTAT_FULL                               0x003                                                                                           /* receive buffer status: full */

#define CANFD_RTIE(n)                                  (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0A4)

#define CANFD_RIE_MASK                                 0x080                                                                                           /* receive interrupt enable */
#define CANFD_ROIE_MASK                                0x040                                                                                           /* receive buffer overrun interrupt enable */
#define CANFD_RFIE_MASK                                0x020                                                                                           /* receive buffer full interrupt enable */
#define CANFD_RAFIE_MASK                               0x010                                                                                           /* receive buffer almost full interrupt enable */
#define CANFD_TPIE_MASK                                0x008                                                                                           /* transmission primary interrupt enable */
#define CANFD_TSIE_MASK                                0x004                                                                                           /* transmission secondary interrupt enable */
#define CANFD_EIE_MASK                                 0x002                                                                                           /* error interrupt enable */
#define CANFD_TSFF_MASK                                0x001                                                                                           /* transmission buffer slot full flag */
#define CANFD_ALLE_MASK                                0x0FE


#define CANFD_RTIF(n)                                  (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0A5)

#define CANFD_RIF_MASK                                 0x080                                                                                           /* receive interrupt flag */
#define CANFD_ROIF_MASK                                0x040                                                                                           /* receive buffer overrun interrupt flag */
#define CANFD_RFIF_MASK                                0x020                                                                                           /* receive buffer full interrupt flag */
#define CANFD_RAFIF_MASK                               0x010                                                                                           /* receive buffer almost full interrupt flag */
#define CANFD_TPIF_MASK                                0x008                                                                                           /* transmission primary interrupt flag */
#define CANFD_TSIF_MASK                                0x004                                                                                           /* transmission secondary interrupt flag */
#define CANFD_EIF_MASK                                 0x002                                                                                           /* error interrupt flag */
#define CANFD_AIF_MASK                                 0x001                                                                                           /* abort interrupt flag */
#define CANFD_ALLF_MASK                                0x0FF                                                                                           /* all the interrupt flag */

#define CANFD_ERRINT(n)                                (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0A6)

#define CANFD_SET_EWARN_MASK                           0x080                                                                                           /* error warning limit reached */
#define CANFD_SET_EPASS_MASK                           0x040                                                                                           /* error passive mode active */
#define CANFD_SET_EPIE_MASK                            0x020                                                                                           /* error passive interrupt enable */
#define CANFD_SET_EPIF_MASK                            0x010                                                                                           /* error passive interrupt flag */
#define CANFD_SET_ALIE_MASK                            0x008                                                                                           /* arbitration lost interrupt enable */
#define CANFD_SET_ALIF_MASK                            0x004                                                                                           /* arbitration lost interrupt flag */
#define CANFD_SET_BEIE_MASK                            0x002                                                                                           /* bus error interrupt enable */
#define CANFD_SET_BEIF_MASK                            0x001                                                                                           /* bus error interrupt flag */

#define CANFD_LIMIT(n)                                 (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0A7)

#define CANFD_SET_AFWL_MASK                            0x0F0                                                                                           /* receive buffer almost full warning limit */
#define CANFD_SET_AFWL_(X)                             ((X%8)<<4)                                                                                      /* receive buffer almost full warning limit configuration */
#define CANFD_SET_EWL_MASK                             0x00F                                                                                           /* programmable error warning limit */
#define CANFD_SET_EWL_(X)                              ((X%16)<<0)                                                                                     /* programmable error warning limit configuration */

#define CANFD_SSEG1(n)                                 (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0A8)

#define CANFD_S_SEG_1_MASK                             0x0FF                                                                                           /* bit timing segment 1 slow speed */
#define CANFD_S_SEG_1_SHIFT                            0                                                                                                       /* s_seg_1 shift */

#define CANFD_SSEG2(n)                                 (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0A9)

#define CANFD_S_SEG_2_MASK                             0x07F                                                                                           /* bit timing segment 2 slow speed */
#define CANFD_S_SEG_2_SHIFT                            0                                                                                                       /* s_seg_2 shift */

#define CANFD_SSJW(n)                                  (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0AA)

#define CANFD_S_SJW_MASK                               0x07F                                                                                           /* synchronization jump width slow speed */
#define CANFD_S_SJW_SHIFT                              0                                                                                                       /* s_sjw shift */

#define CANFD_SPRESC(n)                                (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0AB)

#define CANFD_S_PRESC_MASK                             0x0FF                                                                                           /* prescaler slow speed */
#define CANFD_S_PRESC_SHIFT                            0                                                                                                       /* s_presc shift */

#define CANFD_FSEG1(n)                                 (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0AC)

#define CANFD_F_SEG_1_MASK                             0x01F                                                                                           /* bit timing segment 1 fast speed */
#define CANFD_F_SEG_1_SHIFT                            0                                                                                                       /* f_seg_1 shift*/

#define CANFD_FSEG2(n)                                 (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0AD)

#define CANFD_F_SEG_2_MASK                             0x00F                                                                                           /* bit timing segment 2 fast speed */
#define CANFD_F_SEG_2_SHIFT                            0                                                                                                       /* f_seg_2 shift */

#define CANFD_FSJW(n)                                  (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0AE)

#define CANFD_F_SJW_MASK                               0x00F                                                                                           /* synchronization jump width fast speed */
#define CANFD_F_SJW_SHIFT                              0                                                                                                       /* f_sjw shift */

#define CANFD_FPRESC(n)                                (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0AF)

#define CANFD_F_PRESC_MASK                             0x0FF                                                                                           /* prescaler fast speed */
#define CANFD_F_PRESC_SHIFT                            0                                                                                                       /* f_presc shift */

#define CANFD_EALCAP(n)                                (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0B0)

#define CANFD_KOER_MASK                                0x0E0                                                                                           /* kind of error(error code) */
#define CANFD_SET_NOERR_MASK                           0x000                                                                                           /* no error */
#define CANFD_SET_BIT_ERROR_MASK                       0x020                                                                                           /* bit error */
#define CANFD_SET_FORM_ERROR_MASK                      0x040                                                                                           /* form error */
#define CANFD_SET_STUFF_ERROR_MASK                     0x060                                                                                           /* stuff error */
#define CANFD_SET_ACK_ERROR_MASK                       0x080                                                                                           /* acknowledgement error */
#define CANFD_SET_CRC_ERROR_MASK                       0x0A0                                                                                           /* crc error */
#define CANFD_SET_OTH_ERROR_MASK                       0x0C0                                                                                           /* other error */
#define CANFD_ALC_MASK                                 0x01F                                                                                           /* arbitration lost capture */

#define CANFD_TDC(n)                                   (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0B1)

#define CANFD_SET_TDCEN_MASK                           0x080                                                                                           /* transmitter delay compensation enable */
#define CANFD_SET_SSPOFF_MASK                          0x07F                                                                                           /* secondary sample point offset */
#define CANFD_SSPOFF_SHIFT                             0                                                                                                       /* SSPOFF shift */

#define CANFD_RECNT(n)                                 (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0B2)

#define CANFD_RECNT_MASK                               0x0FF                                                                                           /* receive error count */

#define CANFD_TECNT(n)                                 (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0B3)

#define CANFD_TECNT_MASK                               0x0FF                                                                                           /* transmit error count */

#define CANFD_ACFCTRL(n)                               (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0B4)

#define CANFD_ACFADR_MASK                              0x00F                                                                                           /* acceptance filter address */
#define CANFD_ACFADR(X)                                (X%16)                                                                                          /* acceptance filter address configuration */
#define CANFD_SELMASK                                  0x020                                                                                           /* select acceptance mask */

#define CANFD_TIMECFG(n)                               (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0B5)
#define CANFD_TIMEEN_MASK                              0x001                                                                                           /* time stamping mask bit */
#define CANFD_TIMEEN                                   0x001                                                                                           /* time stamping enable */
#define CANFD_TIMESTAMPING_POSITION_MASK               0x002                                                                                           /* time stamping position mask bit */
#define CANFD_TIMESTAMPING_POSITION_SOF                0x000                                                                                           /* time stamping position SOF */
#define CANFD_TIMESTAMPING_POSITION_EOF                0x002                                                                                           /* time stamping position EOF */

#define CANFD_ACFEN0(n)                                (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0B6)
#define CANFD_ACFEN1(n)                                (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0B7)

#define CANFD_ACCEPTANCE_FILTER_EN_MASK(X)             (1<<(X%8))                                                                                      /* acceptance filter 0 ~ 15 enable */

#define CANFD_ACF0(n)                                  (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0B8)
#define CANFD_ACF1(n)                                  (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0B9)
#define CANFD_ACF2(n)                                  (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0BA)
#define CANFD_ACF3(n)                                  (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0BB)

#define CANFD_AIDE_MASK                                0x20000000                                                                                      /* acceptance mask IDE bit value */
#define CANFD_AIDEE_MASK                               0x40000000                                                                                      /* acceptance mask IDE bit check enable */

#define CANFD_VER0(n)                                  (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0BC)
#define CANFD_VER1(n)                                  (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0BD)
#define CANFD_TBSLOT(n)                                (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0BE)
#define CANFD_TBPTR(n)                                 (n % 5)                                                                                         /* 0: PTB   1~4: STB 4 slots */
#define CANFD_TPF                                      0x040                                                                                           /* set TB slot to filled */
#define CANFD_TPE                                      0x080                                                                                           /* set TB slot to empty */

#define CANFD_TTCFG(n)                                 (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0BF)
#define CANFD_TTEN                                     0x001                                                                                           /* TTCAN enable */
#define CANFD_TTDIS                                    0x000                                                                                           /* TTCAN disable */
#define CANFD_TPRESC_DIV_1                             (0x000 << 1)                                                                            /* TTCAN timer prescaler div 1 */
#define CANFD_TPRESC_DIV_2                             (0x001 << 1)                                                                            /* TTCAN timer prescaler div 2 */
#define CANFD_TPRESC_DIV_4                             (0x002 << 1)                                                                            /* TTCAN timer prescaler div 4 */
#define CANFD_TPRESC_DIV_8                             (0x003 << 1)                                                                            /* TTCAN timer prescaler div 8 */
#define CANFD_TPRESC_DIV_MASK                          (0x003 << 1)                                                                            /* TTCAN timer prescaler div mask */
#define CANFD_TTIF                                     0x008                                                                                           /* TTCAN timer trigger interrupt flag */
#define CANFD_TTIE                                     0x010                                                                                           /* TTCAN timer trigger interrupt enable */
#define CANFD_TEIF                                     0x020                                                                                           /* TTCAN timer trigger error interrupt flag */
#define CANFD_WTIF                                     0x040                                                                                           /* TTCAN watch trigger interrupt flag */
#define CANFD_WTIE                                     0x080                                                                                           /* TTCAN watch trigger interrupt enable */


#define CANFD_REFMSG0(n)                               (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0C0)
#define CANFD_REFMSG1(n)                               (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0C1)
#define CANFD_REFMSG2(n)                               (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0C2)
#define CANFD_REFMSG3(n)                               (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0C3)
#define CANFD_REFID_MASK                               0x1FFFFFFF                                                                                      /* TTCAN reference ID mask */
#define CANFD_REF_IDE                                  0x080                                                                                           /* TTCAN reference ID IDE bit */


#define CANFD_TRIGCFG0(n)                              (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0C4)
#define CANFD_TTPTR(n)                                 (n % 5)                                                                                         /* 0: PTB   1~4: STB 4 slots */

#define CANFD_TRIGCFG1(n)                              (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0C5)
#define CANFD_TTYPE_IMMEDIATE                          0x000                                                                                           /* immediate trigger for immediate transmission */
#define CANFD_TTYPE_TIME                               0x001                                                                                           /* time trigger for receive triggers */
#define CANFD_TTYPE_SINGLE                             0x002                                                                                           /* single shot transmit trigger for excluseive time windows */
#define CANFD_TTYPE_TRANSMIT_START                     0x003                                                                                           /* transmit start trigger for merged arbitration time windows */
#define CANFD_TTYPE_TRANSMIT_STOP                      0x004                                                                                           /* transmit stop trigger for merged arbitration time windows */
#define CANFD_TTYPE_MASK                               0x007                                                                                           /* trigger type mask */
#define CANFD_TEW_MASK                                 0x0F0                                                                                           /* transmit enable window mask */
#define CANFD_TEW(n)                                   (((n-1) % 16)<<4)                                                                       /* transmit enable window 0：1  others: n ticks */

#define CANFD_TTTRIG0(n)                               (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0C6)
#define CANFD_TTTRIG1(n)                               (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0C7)
#define CANFD_TRIGGERTIME(n)                           ((n - 1) & 0xFFFF)                                                                              /* 16bits trigger time */

#define CANFD_TTWTRIG0(n)                              (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0C8)
#define CANFD_TTWTRIG1(n)                              (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0C9)
#define CANFD_WTRIGGERTIME(n)                          (n & 0xFFFF)                                                                                    /* 16bits watch trigger time */

#define CANFD_MEMPROT(n)                                (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0CA)
#define CANFD_MEMSTAT(n)                                (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0CB)
#define CANFD_MEMES0(n)                                 (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0CC)
#define CANFD_MEMES1(n)                                 (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0CD)
#define CANFD_MEMES2(n)                                 (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0CE)
#define CANFD_MEMES3(n)                                 (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0CF)
#define CANFD_SCFG(n)                                   (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0D0)
#define CANFD_DMAC(n)                                   (BASE_CANFD0 + ((CANFD_SEL(n) * 0x1) << 12) + 0x0D4)

struct canfd_regs {
        volatile u8 reserved0[152];                             /* reserved for RBUF and TBUF */
        volatile u8 TTS[8];                                     /* Transmission Time Stamp 0x98-0x9f */

        volatile u8 CFG_STAT;                                   /* CFG_STAT Register 0xA0 */
        volatile u8 TCMD;                                       /* TCMD Register 0xA1 */
        volatile u8 TCTRL;                                      /* TCTRL Register 0xA2 */
        volatile u8 RCTRL;                                      /* RCTRL Register 0xA3 */
        volatile u8 RTIE;                                       /* RTIE Register 0xA4 */
        volatile u8 RTIF;                                       /* RTIF Register 0xA5 */
        volatile u8 ERRINT;                                     /* ERRINT Register 0xA6 */
        volatile u8 LIMIT;                                      /* LIMIT Register 0xA7 */
        volatile u8 SSEG1;                                      /* SSEG1 Register 0xA8 */
        volatile u8 SSEG2;                                      /* SSEG2 Register 0xA9 */
        volatile u8 SSJW;                                       /* SSJW Register 0xAA */
        volatile u8 SPRESC;                                     /* SPRESC Register 0xAB */
        volatile u8 FSEG1;                                      /* FSEG1 Register 0xAC */
        volatile u8 FSEG2;                                      /* FSEG2 Register 0xAD */
        volatile u8 FSJW;                                       /* FSJW Register 0xAE */
        volatile u8 FPRESC;                                     /* FPRESC Register 0xAF */

        volatile u8 EALCAP;                                     /* EALCAP Register 0xB0 */
        volatile u8 TDC;                                        /* TDC Register 0xB1 */
        volatile u8 RECNT;                                      /* RECNT Register 0xB2 */
        volatile u8 TECNT;                                      /* TECNT Register 0xB3 */
        volatile u8 ACFCTRL;                                    /* ACFCTRL Register 0xB4 */
        volatile u8 TIMECFG;                                    /* TIMECFG Register 0xB5 */
        volatile u8 ACFEN0;                                     /* ACFEN0 Register 0xB6 */
        volatile u8 ACFEN1;                                     /* ACFEN1 Register 0xB7 */
        volatile u8 reserved1[4];                               /* reserved for ACF0 to ACF3 */
        //volatile u8 ACF0;                                     /* ACF0 Register 0xB8 */
        //volatile u8 ACF1;                                     /* ACF1 Register 0xB9 */
        //volatile u8 ACF2;                                     /* ACF2 Register 0xBA */
        //volatile u8 ACF3;                                     /* ACF3 Register 0xBB */
        volatile u8 VER0;                                       /* VER0 Register 0xBC */
        volatile u8 VER1;                                       /* VER1 Register 0xBD */
        volatile u8 TBSLOT;                                     /* TBSLOT Register 0xBE */
        volatile u8 TTCFG;                                      /* TTCFG Register 0xBF */

        volatile u8 REF_MSG0;                           /* REF_MSG0 Register 0xC0 */
        volatile u8 REF_MSG1;                           /* REF_MSG1 Register 0xC1 */
        volatile u8 REF_MSG2;                           /* REF_MSG2 Register 0xC2 */
        volatile u8 REF_MSG3;                           /* REF_MSG3 Register 0xC3 */
        volatile u8 TRIG_CFG0;                          /* TRIG_CFG0 Register 0xC4 */
        volatile u8 TRIG_CFG1;                          /* TRIG_CFG1 Register 0xC5 */
        volatile u8 TT_TRIG0;                           /* TT_TRIG0 Register 0xC6 */
        volatile u8 TT_TRIG1;                           /* TT_TRIG0 Register 0xC7 */
        volatile u8 TT_WTRIG0;                          /* TT_WTRIG0 Register 0xC8 */
        volatile u8 TT_WTRIG1;                          /* TT_WTRIG1 Register 0xC9 */

};

/* RBUF and TBUF must be 32bit aceess */
struct canfd_buf {
        volatile u32 RBUF[20];                          /* Receive Buffer Registers 0x00 ~ 0x4F [0x04]control  [0x08]data */
        volatile u32 TBUF[18];                          /* Transmit Buffer Registers 0x50 ~ 0x97 */
        volatile u32 reserved0[8];                      /* reserved 0x98 ~ 0xB7 */
        volatile u32 ACF;                               /* ACF Register 0xB8 ~ 0xBB */
};

#define CAN_ENABLE      1                                                                                               /* function enable */
#define CAN_DISABLE     0                                                                                               /* function disable */

#define CAN_RESET       0                                                                                               /* function bool 0 */
#define CAN_SET         1                                                                                               /* function bool 1 */

#define CANFD_MASK      0x01                                                                                    /* CAN FD type */
#define CAN_MASK        0x00                                                                                    /* CAN type */

/*other macro definition*/
#define CANFD_ACT_RESET                                                 0x001                           /* can controller in RESET */
#define CANFD_NOT_RESET                                                 0x000                           /* can controller not in RESET */

#define CANFD_DATA_FRAME                                                0x000                           /* can data frame */
#define CANFD_REMOTE_FRAME                                              0x001                           /* can remote frame */

#define CANFD_FILTER_STANDARD                                           0x000                           /* can standard filter */
#define CANFD_FILTER_EXTENDED                                           0x001                           /* can extended filter */
#define CANFD_FILTER_BOTH_FRAME                                         0x002                           /* can standard and extended filter */

/*transmit mode*/
//#define XMIT_FULL                                                             0x000                           /* transmit full */
//#define XMIT_SEP_FIFO                                                 0x001                           /* STB FIFO mode */
//#define XMIT_SEP_PRIO                                                 0x002                           /* STB priority mode */
//#define XMIT_PTB_MODE                                                 0x003                           /* PTB mode */

#define CANFD_SET_BIT                                                   0x000                           /* CAN set bit */
#define CANFD_CLR_BIT                                                   0x001                           /* CAN clear bit */

#define CANFD_SEL_PTB                                                   0x000                           /* CAN select PTB */
#define CANFD_SEL_STB                                                   0x001                           /* CAN select STB */

#define CANFD_BOSCH_MODE                                                0x000                           /* CAN select BOSCH mode */
#define CANFD_ISO_MODE                                                  0x001                           /* CAN select ISO mode */

#define CANFD_STB_FIFO_MODE                                             0x000                           /* CAN STB FIFO mode */
#define CANFD_STB_PRIORITY_MODE                                         0x001                           /* CAN STB priority mode */

/* CAN operational and error states */
enum can_state {
        CAN_STATE_ERROR_ACTIVE = 0,                                                                             /* RX/TX error count < 96 */
        CAN_STATE_ERROR_WARNING,                                                                                /* RX/TX error count < 128 */
        CAN_STATE_ERROR_PASSIVE,                                                                                /* RX/TX error count < 256 */
        CAN_STATE_BUS_OFF,                                                                                              /* RX/TX error count >= 256 */
        CAN_STATE_STOPPED,                                                                                              /* Device is stopped */
        CAN_STATE_SLEEPING,                                                                                             /* Device is sleeping */
        CAN_STATE_MAX
};

#define CAN20                   0                                                                                       /* can 2.0 mode */
#define CANFDSLOW               1                                                                                       /* can fd slow speed part */
#define CANFDFAST               2                                                                                       /* can fd fast speed part */

typedef struct __CAN_PARA
{
        struct canfd_regs * canfd_p;                                                                    /* (struct canfd_regs*)BASE_CAN0_FD     (struct canfd_regs*)BASE_CAN1_FD */
        struct canfd_buf * canfd_buf_p;                                                                 /* (struct canfd_regs*)BASE_CAN0_FD     (struct canfd_regs*)BASE_CAN1_FD */
        u8 can_clk;                                                                                                     /* unit: MHz 20? 40? 80?  */
        u32 slow_bitrate;                                                                                               /* unit: bps */
        u32 fast_bitrate;                                                                                               /* unit: bps */
        u8 can_type;                                                                                                    /* 0: CAN_MASK    1: CANFD_MASK */

        struct {
                 unsigned char IDE  : 1;                                                                /* IDE: 0: standard format 1:extended format */
         unsigned char RTR  : 1;                                                                /* RTR: 0: data frame  1: remote frame */
         unsigned char FDF  : 1;                                                                /* FDF: 0: CAN 2.0  1: CAN FD */
         unsigned char BRS  : 1;                                                                /* BRS: 0: normal /slow bit rate  1: switch to fast bit rate */
         unsigned char DLC  : 4;                                                                        /* DLC[3:0] 0 ~ 15 */
                } control;

        struct {
                unsigned int t_s_seg_1;                                                                         /* 0 <= (t_s_seg_1 - 2 = S_Seg_1) <= 255 */
                unsigned int t_s_seg_2;                                                                         /* 0 <= (t_s_seg_2 - 1 = S_Seg_2) <= 127 */
                unsigned int t_s_sjw;                                                                           /* 0 <= (t_s_sjw - 1 = S_SJW) <= 127 */
                unsigned int s_presc;                                                                           /* 0 <= (s_presc - 1 = S_PRESC) <= 255 */
                unsigned int slow_duty_cycle;                                                           /* can fd slow part duty cycle */
                unsigned int slow_baud_err;                                                                     /* can fd slow part baud rate error */
                unsigned int slow_duty_err;                                                                     /* can fd slow part duty cycle error */

                unsigned int t_f_seg_1;                                                                         /* 0 <= (t_f_seg_1 - 2 = F_Seg_1) <= 31 */
                unsigned int t_f_seg_2;                                                                         /* 0 <= (t_f_seg_2 - 1 = F_Seg_2) <= 15 */
                unsigned int t_f_sjw;                                                                           /* 0 <= (t_f_sjw - 1 = F_SJW) <= 15 */
                unsigned int f_presc;                                                                           /* 0 <= (f_presc - 1 = F_PRESC) <= 255  */
                unsigned int fast_duty_cycle;                                                           /* can fd fast part duty cycle */
                unsigned int fast_baud_err;                                                                     /* can fd fast part baud rate error */
                unsigned int fast_duty_err;                                                                     /* can fd fast part duty cycle error */

                unsigned int tdcen;                                                                             /* enable when BRS = 1 */
                unsigned int sspoff;                                                                            /* sspoff value */
                } freq_div_parameters;

        struct {
                u8 ttsen;                                                                                                       /* ttsen:  0: ttcan disable;   1: ttcan enable */
                u32 ref_id;                                                                                                     /* reference message ID */
                u32 rts[2];                                                                                             /* rbuf can frame rts data total 8 bytes */
                } ttcan_para;

        u8 status;                                                                                                              /* can status */
        u32 id;                                                                                                                 /* can id */
        u8 dlc_length;                                                                                                  /* for CAN: 0~8;  for CANFD: 0 ~ 64*/
        u8 dlc_length_word;                                                                                     /* dlc length in words */

        u32 data[16];                                                                                                   /* can frame data total 64 bytes */
} __can_para_t;

#define IDE_0_STANDARD_FORMAT                   0                                                               /* can IDE = 0 standard format */
#define IDE_1_EXTENDED_FORMAT                   1                                                               /* can IDE = 1 extended format */
#define RTR_0_DATA_FRAME                        0                                                               /* can RTR = 0 data format */
#define RTR_1_REMOTE_FRAME                      1                                                               /* can RTR = 1 remote format */
#define FDF_0_CAN2_0_FRAME                      0                                                               /* can FDF = 0 CAN 2.0 format */
#define FDF_1_CANFD_FRAME                       1                                                               /* can FDF = 1 CAN FD format */
#define BRS_0_SLOW_BITRATE                      0                                                               /* can BRS = 0 no freq switch */
#define BRS_1_FAST_BITRATE                      1                                                               /* can BRS = 1 freq switch */

extern __can_para_t can_para[];

/* controller area network (CAN) kernel definitions */

/* special address description flags for the CAN_ID */
#define CAN_EFF_FLAG 0x80000000U                                                                        /* EFF/SFF is set in the MSB */
#define CAN_RTR_FLAG 0x40000000U                                                                        /* remote transmission request */
#define CAN_ERR_FLAG 0x20000000U                                                                        /* error message frame */

/* valid bits in CAN ID for frame formats */
#define CAN_SFF_MASK 0x000007FFU                                                                        /* standard frame format (SFF) */
#define CAN_EFF_MASK 0x1FFFFFFFU                                                                        /* extended frame format (EFF) */
#define CAN_ERR_MASK 0x1FFFFFFFU                                                                        /* omit EFF, RTR, ERR flags */
#define CANXL_PRIO_MASK CAN_SFF_MASK                                                            /* 11 bit priority mask */

#define CANFD_ACF_NUM         16                                                                       /* accept filter number */
#define CANFD_RBUF_SLOT       8                                                                        /* rx buffer total slot */
#define CANFD_TBUF_SLOT       4                                                                        /* tx buffer total slot */
#define CANFD_MAX_BUF_SLOT    (CANFD_RBUF_SLOT > CANFD_TBUF_SLOT ? CANFD_RBUF_SLOT : CANFD_TBUF_SLOT)

#define BITS_OF_BITTIMING_REG  8
#define FBITS_IN_BITTIMING_STR 32
#define SEG_1_SHIFT            0
#define SEG_2_SHIFT            8
#define SJW_SHIFT              16
#define PRESC_SHIFT            24

#define TTSEN_8_32_SHIFT       24
#define RTR_32_8_SHIFT         24

typedef enum
{
        XMIT_FULL     = 0,
        XMIT_SEP_FIFO = 1,
        XMIT_SEP_PRIO = 2,
        XMIT_PTB_MODE = 3

} CANFD_TX_MODE;

typedef enum
{
        XMIT_TSONE = 0,
        XMIT_TSALL = 1,
        XMIT_TTCAN = 2
} CANFD_TX_TYPE;

typedef enum
{
        FILTER_CODE = 0,
        FILTER_MASK = 1
} CANFD_FILTER_SEL;

typedef enum
{
        NORMAL   = 0,
        EXTERNAL = 1,
        INTERNAL = 2
} CANFD_RUN_MODE;

/* Structure for a CAN Message */
typedef struct
{
        u32 id;          // IDE = 1, 29bit EXID; IDE = 0, 11bit STID
        u32 ttsen;       // Transmit time-stamp enable
        u32 rtr;         // Remote Transmission Request bit
        u32 ide;         // ID Extended flag
        u32 fdf;         // CAN FD
        u32 brs;         // Bit Rate Switch
        u32 dlc;         // Data Length Code
        u32 data[64 + 8];// Data Buffer
} canfd_message_t;

typedef struct
{

        union {
                struct
                {
                        u32 seg1 : 8;
                        u32 seg2 : 7;
                        u32 res1 : 1;
                        u32 sjw : 7;
                        u32 res2 : 1;
                        u32 presc : 8;
                };
                u32 seg;
        } SEG;

} CANFD_SEG;


void canfd_soft_rst(u32 n, u8 rst);

/*config CAN FD source fre */
void canfd_set_mod_fre(u32 n, u32 sel, u32 div);

/**
  * @brief  set bits of the register
  * @param  reg_addr: the CANFD register offset
  * @param  val: the mask of the given bit of the register
  */
void canfd_reigister_set_bit(u32 reg_addr, u32 val);

void canfd_clear_irq_bit(u32 reg_addr, u32 val);
/**
  * @brief  clear bits of the register
  * @param  reg_addr: the CANFD register offset
  * @param  val: the mask of the given bit of the register
  */
void canfd_reigister_off_bit(u32 reg_addr, u32 val);


u8 canfd_dlc2len(u8 dlc);
u8 canfd_len2dlc(u8 len);

/**
  * @brief  set or reset the whole controller
  * @param  para: the pointer to the structure of the can
  * @param  reset:
  *   This parameter can be one of the following values:
  *     @arg CANFD_ACT_RESET   : set the can controller
  *     @arg CANFD_NOT_RESET   : reset the can controller
  */
void canfd_set_reset_mode(__can_para_t *para, u8 reset);


/**
  * @brief  get the status of the can controller
  * @param  para: the pointer to the structure of the can
  * @retval
  *     @arg CANFD_ACT_RESET   : the can controller is in reset status
  *     @arg CANFD_NOT_RESET   : the can controller is in normal status
  */
u32 canfd_get_reset_mode(__can_para_t *para);


/**
  * @brief  get the Receive buffer status
  * @param  para: the pointer to the structure of the can
  * @retval The return value can be one of the following values:
  *     @arg CANFD_RSTAT_EMP           : receive buffer status: empty
  *     @arg CANFD_RSTAT_SOME          : receive buffer status: between empty and almost full
  *     @arg CANFD_RSTAT_ALMOSTFULL    : receive buffer status: almost full
  *     @arg CANFD_RSTAT_FULL          : receive buffer status: full
  */
u8 canfd_get_rec_ctrl_status(__can_para_t *para);


/**
  * @brief  get the Transmit buffer status
  * @param  para: the pointer to the structure of the can
  * @retval The return value can be one of the following values:
  *     @arg CANFD_TSSTAT_EMP                  : transmission secondary STATus empty
  *     @arg CANFD_TSSTAT_LESS_EQU_HALF        : transmission secondary STATus less or equal to half
  *     @arg CANFD_TSSTAT_MORE_HALF            : transmission secondary STATus more than half
  *     @arg CANFD_TSSTAT_FULL                 : transmission secondary STATus full
  */
u8 canfd_get_tbuf_ctrl_status(__can_para_t *para);



/**
  * @brief  interrupt configuration
  * @param  para: the pointer to the structure of the can
  * @param  set_int_en:
  *     This parameter can be one of the following values:
  *  @arg  CANFD_RIE_MASK                   : receive interrupt enable
  *  @arg  CANFD_ROIE_MASK                  : receive buffer overrun interrupt enable
  *  @arg  CANFD_RFIE_MASK                  : receive buffer full interrupt enable
  *  @arg  CANFD_RAFIE_MASK                 : receive buffer almost full interrupt enable
  *  @arg  CANFD_TPIE_MASK                  : transmission primary interrupt enable
  *  @arg  CANFD_TSIE_MASK                  : transmission secondary interrupt enable
  *  @arg  CANFD_EIE_MASK                   : error interrupt enable
  * @param  en:
  *    This parameter can be one of the following values:
  *  @arg  CAN_ENABLE                        : enable the interrupt
  *  @arg  CAN_DISABLE                       : disable the interrupt
  */
void canfd_cfg_interrupt(__can_para_t *para, u32 set_int_en, u32 en);


/**
  * @brief  interrupt flag clear
  * @param  para: the pointer to the structure of the can
  * @param  clr_int_flag:
  *     This parameter can be one of the following values:
  *  @arg  CANFD_RIF_MASK                 : receive interrupt flag
  *  @arg  CANFD_ROIF_MASK                : receive buffer overrun interrupt flag
  *  @arg  CANFD_RFIF_MASK                : receive buffer full interrupt flag
  *  @arg  CANFD_RAFIF_MASK               : receive buffer almost full interrupt flag
  *  @arg  CANFD_TPIF_MASK                : transmission primary interrupt flag
  *  @arg  CANFD_TSIF_MASK                : transmission secondary interrupt flag
  *  @arg  CANFD_EIF_MASK                 : error interrupt flag
  *  @arg  CANFD_AIF_MASK                 : abort interrupt flag
  *  @arg  CANFD_ALLF_MASK                : all the interrupt flag
  */
void canfd_clr_cfg_interrupt_flag(__can_para_t *para, u32 clr_int_flag);


/**
  * @brief  interrupt error configuration
  * @param  para: the pointer to the structure of the can
  * @param  err_int_en:
  *     This parameter can be one of the following values:
  *  @arg  CANFD_SET_EPIE_MASK              : error passive interrupt enable
  *  @arg  CANFD_SET_ALIE_MASK              : arbitration lost interrupt enable
  *  @arg  CANFD_SET_BEIE_MASK              : bus error interrupt enable
  * @param  en:
  *    This parameter can be one of the following values:
  *  @arg  CAN_ENABLE                        : enable the interrupt
  *  @arg  CAN_DISABLE                       : disable the interrupt
  */
void canfd_err_interrupt(__can_para_t *para, u32 err_int_en, u32 en);

/**
  * @brief  interrupt error flag clear
  * @param  para: the pointer to the structure of the can
  * @param  clr_int_flag:
  *     This parameter can be one of the following values:
  *  @arg  CANFD_SET_EPIF_MASK            : error passive interrupt flag
  *  @arg  CANFD_SET_ALIF_MASK            : arbitration lost interrupt flag
  *  @arg  CANFD_SET_BEIF_MASK            : bus error interrupt flag
  */
void canfd_clr_err_interrupt_flag(__can_para_t *para, u32 clr_err_flag);

/**
  * @brief  get the given interrupt flag status
  * @param  para: the pointer to the structure of the can
  * @param  get_int_flag:
  *     This parameter can be one of the following values:
    *  @arg     CANFD_RIF_MASK                         : receive interrupt flag
    *  @arg     CANFD_ROIF_MASK                        : receive buffer overrun interrupt flag
    *  @arg     CANFD_RFIF_MASK                        : receive buffer full interrupt flag
    *  @arg     CANFD_RAFIF_MASK                       : receive buffer almost full interrupt flag
    *  @arg     CANFD_TPIF_MASK                        : transmission primary interrupt flag
    *  @arg     CANFD_TSIF_MASK                        : transmission secondary interrupt flag
    *  @arg     CANFD_EIF_MASK                         : error interrupt flag
    *  @arg     CANFD_AIF_MASK                         : abort interrupt flag
  * @retval The return value can be one of the following values:
  *     @arg CAN_SET                                    : the status of the given interrupt flag is set
  *     @arg CAN_RESET                                  : the status of the given interrupt flag is reset
  */
u8 canfd_get_cfg_interrupt(__can_para_t *para, u32 get_int_flag);

/**
  * @brief  get the given error interrupt flag status
  * @param  para: the pointer to the structure of the can
  * @param  get_int_flag:
  *     This parameter can be one of the following values:
  *  @arg  CANFD_SET_EPIF_MASK            : error passive interrupt flag
  *  @arg  CANFD_SET_ALIF_MASK            : arbitration lost interrupt flag
  *  @arg  CANFD_SET_BEIF_MASK            : bus error interrupt flag
  * @retval The return value can be one of the following values:
  *     @arg CAN_SET                                    : the status of the given interrupt flag is set
  *     @arg CAN_RESET                                  : the status of the given interrupt flag is reset
  */
u8 canfd_get_err_interrupt(__can_para_t *para, u32 get_err_flag);

/**
  * @brief  clear all the interrupt flags
  */
void canfd_cfg_int_all_clr(__can_para_t *para);


/**
  * @brief  translate the dlc length to bytes
  * @param  para: the pointer to the structure of the can
  * @param  dlc: the dlc length (unit bytes) of can 2.0 or FD
  * @retval : return the actual dlc length in bytes (0 ~ 64 bytes)
  *
  */
u8 canfd_get_dlc_length(__can_para_t *para, u8 dlc);

/**
  * @brief  get the error type
  * @param  para: the pointer to the structure of the can
  * @retval The return value can be one of the following values:
  *     @arg CANFD_SET_NOERR_MASK              : no error
  *     @arg CANFD_SET_BIT_ERROR_MASK          : bit error
  *     @arg CANFD_SET_FORM_ERROR_MASK         : form error
  *     @arg CANFD_SET_STUFF_ERROR_MASK        : stuff error
  *     @arg CANFD_SET_ACK_ERROR_MASK          : acknowledgement error
  *     @arg CANFD_SET_CRC_ERROR_MASK          : crc error
  *     @arg CANFD_SET_OTH_ERROR_MASK          : other error
  */
u8 canfd_kindoferror(__can_para_t *para);


/**
  * @brief  fill the parameters in the can structure
  * @param  para: the pointer to the structure of the can
  * @param  array: the pointer to the 64 bytes data array
  */
void canfd_fill_parameters(__can_para_t *para, u32* array);


/**
  * @brief  write one frame to the TBUF using the can structure
  * @param  para: the pointer to the structure of the can
  */
void canfd_write_tbuf(__can_para_t *para);

/**
  * @brief  ID filter configuration
  * @param  para: the pointer to the structure of the can
  * @param  filter_channel: filter channnel from 0 to 15
  * @param  acceptance_code: the 29 bits or 11 bits of target ID
  * @param  acceptance_mask: the 29 bits or 11 bits of ID mask
  *  when the bit is 0, it means the input ID bit should be the same as the target ID bit, it will be accept
  *  when the bit is 1, it means whether the input ID bit is 1 or 0, it will be accept
  * @param  id_type: CANFD_FILTER_STANDARD or CANFD_FILTER_EXTENDED or CANFD_FILTER_BOTH_FRAME
  */
void canfd_filter_set(__can_para_t *para, u8 filter_channel, u32 acceptance_code, u32 acceptance_mask, u8 id_type);

/**
  * @brief  receive buffer almost full warning limit configuration
  * @param  para: the pointer to the structure of the can
  * @param  fifo_limit_set: configure the receive buffer almost full warning limit, effective value from 1 ~ 7
  * @retval : return the actual limit configuration value
  */
u8 canfd_afwl_config(__can_para_t *para, u8 fifo_limit_set);


/**
  * @brief  clear the receive buffer until it is empty
  * @param  para: the pointer to the structure of the can
  * although the reset will clear all the receive buffer, it will also clear the other controller configuration
  * so use this method to clear the receive buffer only
  */
void canfd_clear_rbuf(__can_para_t *para);


/**
  * @brief  select the transmit buffer use PTB or STB
  * @param  para: the pointer to the structure of the can
  * @param  ptb_stb:
  *    This parameter can be one of the following values:
  *     @arg CANFD_SEL_PTB   : use PTB
  *     @arg CANFD_SEL_STB   : use STB
  */
void canfd_sel_ptb_stb(__can_para_t *para, u32 ptb_stb);

/**
  * @brief  select the BOSCH(non-ISO) or ISO frame mode
  * @param  para: the pointer to the structure of the can
  * @param  mode:
  *    This parameter can be one of the following values:
  *     @arg CANFD_BOSCH_MODE   : use BOSCH(non-ISO) frame
  *     @arg CANFD_ISO_MODE     : use ISO frame
  */
void canfd_iso_select(__can_para_t *para, u32 mode);


/**
  * @brief  select the FIFO mode or priority mode of STB
  * @param  para: the pointer to the structure of the can
  * @param  mode_sel:
  *    This parameter can be one of the following values:
  *     @arg CANFD_STB_FIFO_MODE        : the oldest frame send first
  *     @arg CANFD_STB_PRIORITY_MODE    : the highest priority frame send first
  */
void canfd_stb_tsmode(__can_para_t *para, u32 mode_sel);







// void canfd_cfg(u8 n, u32 sel, u8 presc)
// {
//  u32 reg_val;
//  pat_goto(0x11);
//  canfd_soft_rst(n, 1);
//  //beforerst
//  //ACODE

//  //AMASK

//  //FD_ISO

//  //F_PRESC F_SEG1 F_SEG2 F_SJW
//  writel(0x010f0f3e, CANFD_FSEG1(n));
//  //S_PRESC S_SEG1 S_SEG2 S_SJW
//  writel(0x0107071e, CANFD_SSEG1(n));
//  u32 reg = readl(CANFD_EALCAP(n));
//  reg &= ~(0x7f<<8);
//  reg |= ((20 | 0x80)<<8);
//  writel(reg, CANFD_EALCAP(n));
//  //XMREN

//  //reset
//  pat_goto(0x12);
//  canfd_soft_rst(n, 0);
//  //after rst
//  reg_val = readl(CANFD_CFG(n));
//  reg_val |= 0x01 << 5;//loop back internal
//  writel(reg_val, CANFD_CFG(n));//id
//  printk("cfg:%x\n", readl(CANFD_CFG(n)) & 0xff);

//  pat_goto(0x13);
//  writel(0x55, CANFD_TBUF(n));//id
//  writel(0x11223308, CANFD_TBUF(n) + 4);
//  writel(0x55667788, CANFD_TBUF(n) + 8);
//  writel(0x55667788, CANFD_TBUF(n) + 12);
//  printk("%x %x %x \n",readl(CANFD_TBUF(n)),  readl(CANFD_TBUF(n)+4), readl(CANFD_TBUF(n)+8));

//  pat_goto(0x14);
//  reg_val = readl(CANFD_CFG(n));
//  reg_val |= (0x01 << 4) << 8;
//  writel(reg_val, CANFD_CFG(n));

//  while(readl(CANFD_CFG(n)) & 0x02) {};
//  pat_goto(0x15);

//  printk("CANFD_CFG:%x\n", readl(CANFD_CFG(n)));
//  printk("CANFD_RTIE:%x\n", readl(CANFD_RTIE(n)));
//  while((readb(CANFD_RTIF(n)) & 0x80) == 0) {};
//  //while(((readl(CANFD_RTIE(n))>>8 ) & 0x80) == 0) {};
//  pat_goto(0x16);

//  printk("%x %x %x \n", readl(CANFD_RBUF(n)), readl(CANFD_RBUF(n)+4), readl(CANFD_RBUF(n) + 8));

// }



static void can_fd0_int_handler();

static void can_fd1_int_handler();

void canfd_irq_handler(u32 n);

int canfd_set_xmit_mode(u32 n, CANFD_TX_MODE mode);

void canfd_frame_print(canfd_message_t* frame);

void canfd_frame_print_cia603(canfd_message_t* frame);

/*Transmit a CAN Message*/
void canfd_tx_load_msg_2_buf(u32 n, canfd_message_t* frame);

s32 canfd_tx_frame(u32 n, CANFD_TX_MODE mode, CANFD_TX_TYPE type, u8 f_sum, canfd_message_t* frame);

/*Receive a CAN Message*/
s32 canfd_rx_frame(u32 n, canfd_message_t* frame);

// only config when reset = 1
s32 canfd_filter_cfg(u8 n, u8 acfadr, u8 selmask, u32 ACF);

s32 canfd_filter_en(u8 n, u8 acfadr, u8 en);

s32 canfd_cia603_en(u8 n, u8 pos, u8 en);

//static void canfd_tx_interrupt(u8 n, u8 isr);

//static void canfd_rxfull_interrupt(u8 n, u8 isr);

u32 canfd_interrupt(u8 n);

//static int canfd_bittime_cfg(u8 n, CANFD_SEG* s_seg, CANFD_SEG* f_seg);

s32 cal_seg(u32 sou_fre, u32 baud, CANFD_SEG* seg, u32 fast);

/**
  * @brief  calculate the best seg and presc parameters
  * @param  para: the pointer to the structure of the can
  * @param  baudrate: set the needed baudrate unit in bps
  * @param  duty_cycle: 50 ~ 100 (%) = seg_1 / (seg_1 + seg_2)
  * @param  mode: CAN20  or CANFDSLOW or CANFDFAST
  */
//static void canfd_get_best_presc(__can_para_t *para, unsigned int baudrate, unsigned int duty_cycle, unsigned int mode);


/**
  * @brief  config the best seg and presc parameters
  * @param  para: the pointer to the structure of the can
  */
u8 canfd_parameters_cal(__can_para_t *para);

s32 canfd_init(u32 n, u32 run_mode, u32 s_baud, u32 f_baud);

/**
  * @brief  CiA603 mode configuration
  * @param  para: the pointer to the structure of the can
  * @param  en:
  *   This parameter can be one of the following values:
  *     @arg CAN_ENABLE    : enable CiA603
  *     @arg CAN_DISABLE   : disable CiA603
  * @param  position:
  *   This parameter can be one of the following values:
  *     @arg CANFD_TIMESTAMPING_POSITION_SOF    : time stamping position SOF
  *     @arg CANFD_TIMESTAMPING_POSITION_EOF    : time stamping position EOF
  */
void canfd_ttcan_cia603_cfg(__can_para_t *para, u32 en , u32 position);

/**
  * @brief  switch the tbuf slot in TTCAN mode and set full or empty
  * @param  para: the pointer to the structure of the can
  * @param  full_empty:
  *   This parameter can be one of the following values:
  *     @arg CANFD_TPF    : set the select slot as full
  *     @arg CANFD_TPE    : set the select slot as empty
  * @param  slot_num:   0 ~  4   0: PTB   1~4: STB 4 slots
  */
void canfd_ttcan_tbslot_pointer(__can_para_t *para, u32 full_empty, u32 slot_num);

/**
  * @brief  TTCAN mode enable
  * @param  para: the pointer to the structure of the can
  * @param  en:
  *   This parameter can be one of the following values:
  *     @arg CANFD_TTEN    : enable TTCAN
  *     @arg CANFD_TTDIS   : disable TTCAN
  */
void canfd_ttcan_timetrigger_en(__can_para_t *para, u32 en);

/**
  * @brief  timer trigger interrupt configuration
  * @param  para: the pointer to the structure of the can
  * @param  set_int_en:
  *     This parameter can be one of the following values:
  *  @arg  CANFD_TTIE                   : TTCAN timer trigger interrupt enable
  *  @arg  CANFD_WTIE                   : TTCAN watch trigger interrupt enable
  * @param  en:
  *    This parameter can be one of the following values:
  *  @arg  CAN_ENABLE                        : enable the interrupt
  *  @arg  CAN_DISABLE                       : disable the interrupt
  */
void canfd_ttcan_interrupt(__can_para_t *para, u32 set_int_en, u32 en);

/**
  * @brief  get the ttcan interrupt configuration
  * @param  para: the pointer to the structure of the can
  * @param  get_int_flag:
  *     This parameter can be one of the following values:
  *  @arg  CANFD_TTIF                   : TTCAN timer trigger interrupt flag
  *  @arg  CANFD_TEIF                   : TTCAN timer trigger error interrupt flag
  *  @arg  CANFD_WTIF                   : TTCAN watch trigger interrupt flag
  * @retval
  *     @arg CAN_SET     : the flag is in set status
  *     @arg CAN_RESET   : the flag is in unset status
  */
u8 canfd_ttcan_get_cfg_interrupt(__can_para_t *para, u32 get_int_flag);

/**
  * @brief  timer trigger interrupt flag clear
  * @param  para: the pointer to the structure of the can
  * @param  clr_int_flag:
  *     This parameter can be one of the following values:
  *  @arg  CANFD_TTIF                   : TTCAN timer trigger interrupt flag
  *  @arg  CANFD_WTIF                   : TTCAN watch trigger interrupt flag
  *  @arg  CANFD_TEIF                   : TTCAN timer trigger error interrupt flag
  */
void canfd_ttcan_clr_cfg_interrupt_flag(__can_para_t *para, u32 clr_int_flag);

/**
  * @brief  TTCAN timer prescaler
  * @param  para: the pointer to the structure of the can
  * @param  div:
  *     This parameter can be one of the following values:
  *  @arg  CANFD_TPRESC_DIV_1                   : TTCAN timer prescaler div 1
  *  @arg  CANFD_TPRESC_DIV_2                   : TTCAN timer prescaler div 2
  *  @arg  CANFD_TPRESC_DIV_4                   : TTCAN timer prescaler div 4
  *  @arg  CANFD_TPRESC_DIV_8                   : TTCAN timer prescaler div 8
  */
void canfd_ttcan_prescaler(__can_para_t *para, u32 div);

/**
  * @brief  TTCAN reference message configure
  * @param  para: the pointer to the structure of the can
  * @param  id:  the 11 bits or 29 bits ID
  */
void canfd_ttcan_ref_id_cfg(__can_para_t *para, u32 id);

/**
  * @brief  TTCAN tbuf trigger pointer configure
  * @param  para: the pointer to the structure of the can
  * @param  slot_num:  0: PTB   1~4: STB 4 slots
  */
void canfd_ttcan_trigger_pointer(__can_para_t *para, u32 slot_num);

/**
  * @brief  TTCAN tbuf trigger type
  * @param  para: the pointer to the structure of the can
  * @param  type:
  *   This parameter can be one of the following values:
  *     @arg CANFD_TTYPE_IMMEDIATE         : immediate trigger for immediate transmission
  *     @arg CANFD_TTYPE_TIME              : time trigger for receive triggers
  *     @arg CANFD_TTYPE_SINGLE            : single shot transmit trigger for excluseive time windows
  *     @arg CANFD_TTYPE_TRANSMIT_START    : transmit start trigger for merged arbitration time windows
  *     @arg CANFD_TTYPE_TRANSMIT_STOP     : transmit stop trigger for merged arbitration time windows
  */
void canfd_ttcan_trigger_type(__can_para_t *para, u32 type);

/**
  * @brief  TTCAN transmit enable window configure
  * @param  para: the pointer to the structure of the can
  * @param  tew:   transmit enable window 0 ~ 16  0 means 1
  */
void canfd_ttcan_transmit_enable_win(__can_para_t *para, u32 tew);

/**
  * @brief  TTCAN trigger time configure
  * @param  para: the pointer to the structure of the can
  * @param  triggertime:   0 ~ 0x10000
  */
void canfd_ttcan_trigger_time_cfg(__can_para_t *para, u32 triggertime);

/**
  * @brief  TTCAN watch trigger time configure
  * @param  para: the pointer to the structure of the can
  * @param  watchtriggertime:   0 ~ 0xFFFF
  */
void canfd_ttcan_watch_trigger_time_cfg(__can_para_t *para, u32 watchtriggertime);


s32 init_canfd(u32 canfd_num, u32 mod_fre);
void canfd_irq_register(u8 num, cpu_irq_fun_t irqhandle);
void canfd_irq_unregister(u8 num);
#endif
