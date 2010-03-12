#include "os.h"
#include <mp.h>
#include <libsec.h>

void
main(void)
{
	mpint *z = mpnew(0);
	mpint *p = mpnew(0);
	mpint *q = mpnew(0);
	mpint *nine = mpnew(0);

	fmtinstall('B', mpfmt);
	strtomp("2492491", nil, 16, z);	/* 38347921 = x*y = (2**28-9)/7,  */
				/*    an example of 3**(n-1)=1 mod n */
	strtomp("15662C00E811", nil, 16, p);/* 23528569104401, a prime */
	uitomp(9, nine);

	if(probably_prime(z, 5) == 1)
		fprint(2, "tricked primality test\n");
	if(probably_prime(nine, 5) == 1)
		fprint(2, "9 passed primality test!\n");
	if(probably_prime(p, 25) == 1)
		fprint(2, "ok\n");

	DSAprimes(q, p, nil);
	print("q=%B\np=%B\n", q, p);

	exits(0);
}

/* example output, checked with Maple: */
/* seed EB7B6E35F7CD37B511D96C67D6688CC4DD440E1E */
/* q=E0F0EF284E10796C5A2A511E94748BA03C795C13 */
/*  = 1284186945063585093695748280224501481698995297299 */
/* p=C41CFBE4D4846F67A3DF7DE9921A49D3B42DC33728427AB159CEC8CBBDB12B5F0C244F1A734AEB9840804EA3C25036AD1B61AFF3ABBC247CD4B384224567A863A6F020E7EE9795554BCD08ABAD7321AF27E1E92E3DB1C6E7E94FAAE590AE9C48F96D93D178E809401ABE8A534A1EC44359733475A36A70C7B425125062B1142D */
/*  = 137715385439333164327584575331308277462546592976152006175830654712456008630139443747529133857837818585400418619916530061955288983751958831927807888408309879880101870216437711393638413509484569804814373511469405934988856674935304074081350525593807908358867354528898618574659752879015380013845760006721861915693 */
/* r=DF310F4E54A5FEC5D86D3E14863921E834113E060F90052AD332B3241CEF2497EFA0303D6344F7C819691A0F9C4A773815AF8EAECFB7EC1D98F039F17A32A7E887D97251A927D093F44A55577F4D70444AEBD06B9B45695EC23962B175F266895C67D21C4656848614D888A4 */
/*  = 107239359478548771267308764204625458348785444483302647285245969203446101233421655396874997253111222983406676955642093641709149748793954493558324738441197139556917622937892491175016280660608595599724194374948056515856812347094848443460715881455884639869144172708 */
/* g=2F1C308DC46B9A44B52DF7DACCE1208CCEF72F69C743ADD4D2327173444ED6E65E074694246E07F9FD4AE26E0FDDD9F54F813C40CB9BCD4338EA6F242AB94CD410E676C290368A16B1A3594877437E516C53A6EEE5493A038A017E955E218E7819734E3E2A6E0BAE08B14258F8C03CC1B30E0DDADFCF7CEDF0727684D3D255F1 */
/*  = 33081848392740465806285326014906437543653045153885419334085917570615301913274531387168723847139029827598735376746057461417880810924280288611116213062512408829164220104555543445909528701551198146080221790002337033997295756585193926863581671466708482411159477816144226847280417522524922667065714073338662508017 */
