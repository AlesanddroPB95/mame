//ES3 Games include:
//Mach Storm (Namco, 2013)
//Wangan Midnight Maximum Tune 6 (Namco, 2018)
//Wangan Midnight Maximum Tune 5 (includes DX+) (Namco, 2014)
//Wangan Midnight Maximum Tune 6R (Namco, 2020)
//Mario Kart DX (Namco, 2013)
//Tekken 7 (includes Fated Retribution and Fated Retribution Round 2) (Namco, 2015)
//Lost Land Adventure (Namco, 2014)
//Time Crisis 5 (Namco, 2015)
//Pokken Tournament (Namco, 2015)
//Lucasfilm's Star Wars: Battle Pod (Namco, 2014)
//Super Alpine Racer (Namco & Raw Thrills, 2014)

#include "emu.h"
#include "cpu/i386/i386.h"
#include "machine/pci.h"
#include "machine/i82875p.h"
#include "machine/i6300esb.h"
#include "machine/pci-usb.h"
#include "machine/pci-apic.h"
#include "machine/pci-sata.h"
#include "machine/pci-smbus.h"
#include "machine/i82541.h"
#include "machine/segabb.h"
#include "sound/pci-ac97.h"
#include "sound/sb0400.h"
#include "video/gf7600gs.h"

class namcoes3_state : public driver_device
{
public:
	namcoes3_state(const machine_config &mconfig, device_type type, const char *tag);

	void namcoes3(machine_config &config);

protected:
	virtual void machine_start() override;
	virtual void machine_reset() override;
};

namcoes3_state::namcoes3_state(const machine_config &mconfig, device_type type, const char *tag) : driver_device(mconfig, type, tag)
{
}

void namcoes3_state::machine_start()
{
}

void namcoes3_state::machine_reset()
{
}

void namcoes3_state::namcoes3(machine_config &config)
{
	PENTIUM4(config, "maincpu", 28000000U*5); /* Actually Celeron D at 2,8 GHz */

	PCI_ROOT                (config, ":pci",           0);
	I82875P_HOST            (config, ":pci:00.0",      0,                   0x103382c0, "maincpu", 512*1024*1024);
	I82875P_AGP             (config, ":pci:01.0",      0);
	GEFORCE_7600GS          (config, ":pci:01.0:00.0", 0,                   0x10de02e1);
	I82875P_OVERFLOW        (config, ":pci:06.0",      0,                   0x103382c0);
	PCI_BRIDGE              (config, ":pci:1c.0",      0, 0x808625ae, 0x02);
	I82541                  (config, ":pci:1c.0:00.0", 0,                   0x103382c0);
	USB_UHCI                (config, ":pci:1d.0",      0, 0x808625a9, 0x02, 0x103382c0);
	USB_UHCI                (config, ":pci:1d.1",      0, 0x808625aa, 0x02, 0x103382c0);
	I6300ESB_WATCHDOG       (config, ":pci:1d.4",      0,                   0x103382c0);
	APIC                    (config, ":pci:1d.5",      0, 0x808625ac, 0x02, 0x103382c0);
	USB_EHCI                (config, ":pci:1d.7",      0, 0x808625ad, 0x02, 0x103382c0);
	PCI_BRIDGE              (config, ":pci:1e.0",      0, 0x8086244e, 0x0a);
	SB0400                  (config, ":pci:1e.0:02.0", 0,                   0x11021101);
	SEGA_LINDBERGH_BASEBOARD(config, ":pci:1e.0:03.0", 0);
	I6300ESB_LPC            (config, ":pci:1f.0",      0);
	LPC_ACPI                (config, ":pci:1f.0:acpi", 0);
	LPC_RTC                 (config, ":pci:1f.0:rtc",  0);
	LPC_PIT                 (config, ":pci:1f.0:pit",  0);
	SATA                    (config, ":pci:1f.2",      0, 0x808625a3, 0x02, 0x103382c0);
	SMBUS                   (config, ":pci:1f.3",      0, 0x808625a4, 0x02, 0x103382c0);
	AC97                    (config, ":pci:1f.5",      0, 0x808625a6, 0x02, 0x103382c0);
}

#define ES3_BIOS \
	ROM_REGION32_LE(0x100000, ":pci:1f.0", 0) /* PC bios, location 3j7 */ \
	ROM_SYSTEM_BIOS(0, "bios0", "6.0.0010 alternate version") \
	ROMX_LOAD("NAMCOES3BIOS.bin", 0x00000, 0x100000, CRC(10dd9b76) SHA1(1fdf1f921bc395846a7c3180fbdbc4ca287a9670), ROM_BIOS(0) ) \
\
	ROM_REGION(0x400000, ":pci:1e.0:03.0", 0) /* Baseboard MPC firmware */ \
	ROM_LOAD("NAMCOS22IO.bin", 0x000000, 0x400000, CRC(c3b021a4) SHA1(1b6938a50fe0e4ae813864649eb103838c399ac0)) \
	\
	ROM_REGION32_LE(0x10000, ":pci:01.0:00.0", 0) /* Geforce bios extension (custom for the card) */ \
	ROM_LOAD("NAMCOES3GFORCE.BIN", 0x00000, 0x10000, CRC(f78d14d7) SHA1(f129787e487984edd23bf344f2e9500c85052275)) \

#define ES4_BIOS \
	ROM_REGION32_LE(0x100000, ":pci:1f.0", 0) /* PC bios, location 3j7 */ \
	ROM_SYSTEM_BIOS(0, "bios0", "6.0.0010 alternate version") \
	ROMX_LOAD("NAMCOES3BIOS.bin", 0x00000, 0x100000, CRC(10dd9b76) SHA1(1fdf1f921bc395846a7c3180fbdbc4ca287a9670), ROM_BIOS(0) ) \
\
	ROM_REGION(0x400000, ":pci:1e.0:03.0", 0) /* Baseboard MPC firmware */ \
	ROM_LOAD("NAMCOS22IO.bin", 0x000000, 0x400000, CRC(c3b021a4) SHA1(1b6938a50fe0e4ae813864649eb103838c399ac0)) \
	\
	ROM_REGION32_LE(0x10000, ":pci:01.0:00.0", 0) /* Geforce bios extension (custom for the card) */ \
	ROM_LOAD("NAMCOES4GFORCE.BIN", 0x00000, 0x10000, CRC(f78d14d7) SHA1(f129787e487984edd23bf344f2e9500c85052275)) \

#define ES3RT_BIOS \
	ROM_REGION32_LE(0x100000, ":pci:1f.0", 0) /* PC bios, location 3j7 */ \
	ROM_SYSTEM_BIOS(0, "bios0", "6.0.0010 alternate version") \
	ROMX_LOAD("NAMCOES3BIOS.bin", 0x00000, 0x100000, CRC(10dd9b76) SHA1(1fdf1f921bc395846a7c3180fbdbc4ca287a9670), ROM_BIOS(0) ) \
\
	ROM_REGION(0x400000, ":pci:1e.0:03.0", 0) /* Baseboard MPC firmware */ \
	ROM_LOAD("BetsonI/OBoard.bin", 0x000000, 0x400000, CRC(c3b021a4) SHA1(1b6938a50fe0e4ae813864649eb103838c399ac0)) \
	\
	ROM_REGION32_LE(0x10000, ":pci:01.0:00.0", 0) /* Geforce bios extension (custom for the card) */ \
	ROM_LOAD("NAMCOES3GFORCE.BIN", 0x00000, 0x10000, CRC(f78d14d7) SHA1(f129787e487984edd23bf344f2e9500c85052275)) \


ROM_START(namco_es3)
	ES3_BIOS
ROM_END

ROM_START(namco_es4)
	ES4_BIOS
ROM_END

ROM_START(rawt_es3)
	ES3RT_BIOS
ROM_END


ROM_START(timecrs5)
	ES3_BIOS

	ROM_REGION(0x2000, ":pic", 0)
	ROM_LOAD("TimeCrisis5Dongle.bin", 0, 0x2000, CRC(ef4a120c) SHA1(fcc0386fa708af9e010e40e1d259a6bd95e8b9e2))  // PIC was added from Rev A

	DISK_REGION("hdd")
	DISK_IMAGE_READONLY("TimeCrisis5RevB", 0, SHA1(67f2565338f1e8df4c6cfc83447f490f75541b16))
ROM_END

ROM_START(timecrs5a)
	ES3_BIOS

	ROM_REGION(0x2000, ":pic", 0) // PIC security 253-5508-0427 / 317-0427-COM
	ROM_LOAD("TimeCrisis5Dongle.bin", 0, 0x2000, CRC(ef4a120c) SHA1(fcc0386fa708af9e010e40e1d259a6bd95e8b9e2))  // PIC was added from Rev A

	DISK_REGION("hdd")
	DISK_IMAGE_READONLY("TimeCrisis5", 0, SHA1(46544e28735f55418dd78bd19446093874438264))
ROM_END

ROM_START(starwsbp)
	ES3_BIOS

	ROM_REGION(0x2000, ":pic", 0) // PIC security 253-5508-0438 / 317-0438-COM
	ROM_LOAD("StarWarsDongle.bin", 0, 0x2000, CRC(9aeb15d3) SHA1(405ddc44b2b40b72cfe2a081a0d5e43ceb9a380e))

	DISK_REGION("hdd")
	DISK_IMAGE_READONLY("StarWarsBattlePod", 0, NO_DUMP)
ROM_END

ROM_START(lostland)
	ES3_BIOS

	ROM_REGION(0x2000, ":pic", 0) // PIC security 253-5508-0440 / 317-0440-COM
	ROM_LOAD("LostLandDongle.bin", 0, 0x2000, CRC(8d09e717) SHA1(6b25982f7042541874115d33ea5d0c028140a962))

	DISK_REGION("hdd")
	DISK_IMAGE_READONLY("LostLandAdventure", 0, NO_DUMP)
ROM_END

ROM_START(pointblx)
	ES4_BIOS

	ROM_REGION(0x2000, ":pic", 0) // PIC security 253-5508-0442 / 317-0442-COM
	ROM_LOAD("PointBlankXDongle.bin", 0, 0x2000, CRC(b706efbb) SHA1(97c2b65e521113c5201f0b588fcb37a39148a637))

	DISK_REGION("hdd")
	DISK_IMAGE_READONLY("GunbulletX", 0, NO_DUMP)
ROM_END

ROM_START(mkdx110j)
	ES3_BIOS

	ROM_REGION(0x2000, ":pic", 0) // PIC security 253-5508-0452 / 317-0452-COM (to verify, may be the one for OutRun 2 Special Tours)
	ROM_LOAD("MarioKartDXDongle.bin", 0, 0x2000, CRC(f5b7bb3f) SHA1(6b179b255b3d29e5ce61902eeae4da07177a2943))

	DISK_REGION("hdd")
	DISK_IMAGE_READONLY("MarioKartArcadeGPDLX_1.10_JAPAN", 0, NO_DUMP)
ROM_END

ROM_START(mkdx118j)
	ES3_BIOS

	ROM_REGION(0x2000, ":pic", 0) // PIC security 253-5508-0434 / 317-0434-COM
	ROM_LOAD("MarioKartDXDongle.bin", 0, 0x2000, CRC(f5b7bb3f) SHA1(6b179b255b3d29e5ce61902eeae4da07177a2943))

	DISK_REGION("hdd")
	DISK_IMAGE_READONLY("MarioKartArcadeGPDLX_1.18_JAPAN", 0, NO_DUMP)
ROM_END

ROM_START(mkdx)
	ES3_BIOS

	ROM_REGION(0x2000, ":pic", 0) // PIC security 253-5508-0506 / 317-0506-JPN
	ROM_LOAD("MarioKartDXDongle.bin", 0, 0x2000, CRC(f5b7bb3f) SHA1(6b179b255b3d29e5ce61902eeae4da07177a2943))

	DISK_REGION("hdd")
	DISK_IMAGE_READONLY("MarioKartArcadeGPDX_EXPORT_RevB", 0, SHA1(1fd689753c4b70dff0286cb7f623ee7fd439db62))
ROM_END

ROM_START(mkdx104u)
	ES3_BIOS

	ROM_REGION(0x2000, ":pic", 0) // PIC security 253-5508-0491 / 317-0491-COM
	ROM_LOAD("MarioKartDXDongle.bin", 0, 0x2000, CRC(f5b7bb3f) SHA1(6b179b255b3d29e5ce61902eeae4da07177a2943))

	DISK_REGION("hdd")
	DISK_IMAGE_READONLY("MarioKartArcadeGPDX_EXPORT_RevA", 0, SHA1(da1aacee9e32e813844f4d434981e69cc5c80682))
ROM_END

ROM_START(gundames3)
	ES3_BIOS

	DISK_REGION("hdd")
	DISK_IMAGE_READONLY("GundamES3", 0, SHA1(256d9e8a6d61e1bcf65b17b8ed70fbc58796f7b1))
ROM_END

ROM_START(machstom)
	ES3_BIOS

	ROM_REGION(0x2000, ":pic", 0) // PIC security 253-5508-0486E / 317-0486-COM
	ROM_LOAD("MachstormDongle.bin", 0, 0x2000, NO_DUMP)

	DISK_REGION("hdd")
	DISK_IMAGE_READONLY("Machstorm_Japan", 0, SHA1(e43e6d22fab4eceb81db8309e4634e049d9c41e6))
ROM_END

ROM_START(mchstrmx)
	ES3_BIOS

	ROM_REGION(0x2000, ":pic", 0) // PIC security 253-5508-0486E / 317-0486-COM
	ROM_LOAD("MachstormDongle.bin", 0, 0x2000, NO_DUMP)

	DISK_REGION("hdd")
	DISK_IMAGE_READONLY("Machstorm_International", 0, SHA1(b1919f28539afec4c4bc52357e5210a090b5ae32))
ROM_END

ROM_START(tekken7)
	ES3_BIOS

	ROM_REGION(0x2000, ":pic", 0) // PIC security 253-5508-0504 / 317-0504-COM
	ROM_LOAD("Tekken7Dongle.bin", 0, 0x2000, CRC(ae7eaea8) SHA1(187e417e0b5543d95245364b547925426aa9f80e))

	DISK_REGION("hdd")
	DISK_IMAGE_READONLY("TekkenVII", 0, SHA1(914aa23ece8aaf0f1942f77272b3a87d10f7a7db))
ROM_END

ROM_START(tekken71)
	ES3_BIOS

	ROM_REGION(0x2000, ":pic", 0) // PIC security 253-5508-0550 / 317-0550-JPN
	ROM_LOAD("Tekken7FRDongle.bin", 0, 0x2000, CRC(7e247f13) SHA1(d416b0e7742b32eb31443967e84ef93fc9e56dfb))

	DISK_REGION("hdd")
	DISK_IMAGE_READONLY("Tekken7FatedRetribution", 0, NO_DUMP)
ROM_END

ROM_START(tekken72)
	ES3_BIOS

	ROM_REGION(0x2000, ":pic", 0) // PIC security 253-5508-0512 / 317-0512-COM
	ROM_LOAD("Tekken7FRR2Dongle.bin", 0, 0x2000, NO_DUMP)

	DISK_REGION("hdd")
	DISK_IMAGE_READONLY("Tekken7FatedRetributionR2", 0, SHA1(0c3b87b7309cf67ece54fc5cd5bbcfc7dc04083f))
ROM_END

ROM_START(wmmt5)
	ES3_BIOS

	ROM_REGION(0x2000, ":pic", 0) // PIC security 253-5508-0540 / 317-0540-COM
	ROM_LOAD("Wangan5JPNDongle.bin", 0, 0x2000, CRC(fd9a7bc0) SHA1(140b05573e25a41c1237c7a96c8e099efbfd75b8))

	DISK_REGION("hdd")
	DISK_IMAGE_READONLY("WanganMT5_Japan", 0, SHA1(1f3401b652c45db2b843360aff9cda862c2832c0))
ROM_END

ROM_START(wmmt6)
	ES3_BIOS

	ROM_REGION(0x2000, ":pic", 0) // PIC security id unknown
	ROM_LOAD("Wangan6JPNDongle.bin", 0, 0x2000, CRC(524bc69a) SHA1(c79b6bd384196c169e40e623f4c80c8b9eb11f81))
ROM_END

ROM_START(es3Win7)
	ES3_BIOS

	DISK_REGION("dvd")
	DISK_IMAGE_READONLY("Win7OS", 0, SHA1(362ac028ba19ba4762678953a033034a5ee8ad53))
ROM_END

//Super Alpine Racer, by default, it uses a Raw Thrills I/O Board and Dongle, making it a different setup

ROM_START(alpiner4)
	ES3RT_BIOS

	ROM_REGION(0x2000, ":pic", 0) // PIC security 253-5508-0540 / 317-0540-COM
	ROM_LOAD("RTHASP_Alpine_Dongle.bin", 0, 0x2000, CRC(fd9a7bc0) SHA1(140b05573e25a41c1237c7a96c8e099efbfd75b8))

	DISK_REGION("hdd")
	DISK_IMAGE_READONLY("SuperAlpineRacer", 0, SHA1(1f3401b652c45db2b843360aff9cda862c2832c0)) // can be changed to English by accesing the service menu
ROM_END


GAME(2012, namco_es3,  0,        namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "Namco ES3 Bios",                           MACHINE_IS_BIOS_ROOT)
GAME(2012, rawth_es3,  0,        namcoes3, 0, namcoes3_state, empty_init, ROT0, "Raw Thrills", "Super Alpine Racer Bios",            MACHINE_IS_BIOS_ROOT)
GAME(2014, namco_es4,  0,        namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "Namco ES4 Bios",                           MACHINE_IS_BIOS_ROOT)
GAME(2005, timecrs5, namco_es3,  namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "Time Crisis 5 (Rev B)",                    MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
GAME(2005, timecrs5a, timecrs5,  namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "Time Crisis 5 (Rev A)",                    MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
GAME(2005, starwsbp,  namco_es3, namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "Star Wars Battle Pod (Export)",            MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
GAME(2006, lostland,  namco_es3, namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "Lost Land Adventure (Export)",             MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
GAME(2006, pointblx,  namco_es4, namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "Point Blank X (Export)",                   MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
GAME(2015, mkdx110j,  mkdx,      namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "Mario Kart GP DX (Japan, Ver. 1.10/JP)",   MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
GAME(2020, mkdx118j,  mkdx,      namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "Mario Kart GP DX (Japan, Ver. 1.18/JP)",   MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
GAME(2016, mkdx106u,  mkdx,      namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "Mario Kart GP DX (Export, Ver. 1.06/OF)",  MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
GAME(2015, mkdx104u,  mkdx,      namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "Mario Kart GP DX (Export, Ver. 1.04/EX)",  MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
GAME(2007, gundames3, namco_es3, namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "Gundam",                                   MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
GAME(2007, machstom,  namco_es3, namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "MachStorm (Japan)",                        MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
GAME(2007, mchstrmx,  machstom,  namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "MachStorm (Export)",                       MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
GAME(2007, tekken7,   tekken72,  namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "Tekken 7",                                 MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
GAME(2008, tekken71,  tekken72,  namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "Tekken 7 Fated Retribution",               MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
GAME(2008, tekken72,  namco_es3, namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "Tekken 7 Fated Retribution Round 2",       MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
GAME(2014, wmmt5,     namco_es3, namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "Wangan Midnight Maximum Tune 5 (Japan)",   MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
GAME(2018, wmmt6,     namco_es3, namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "Wangan Midnight Maximum Tune 6 (Japan)",   MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
GAME(200?, es3w7,     namco_es3, namcoes3, 0, namcoes3_state, empty_init, ROT0, "Namco", "Windows 7 Restore disc for ES3",           MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
GAME(2014, alpiner4,  rawth_es3, namcoes3, 0, namcoes3_state, empty_init, ROT270, "Namco", "Super Alpine Racer (Japan)",             MACHINE_NOT_WORKING|MACHINE_UNEMULATED_PROTECTION|MACHINE_NO_SOUND)
