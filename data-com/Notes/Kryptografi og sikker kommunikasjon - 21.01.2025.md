1. Tre sikkerhetsfunksjoner (CIA)  hva disse innebærer
	- Konfidensialitet
	- Integritet
	- Autensitet
2. Tre kryptografiske metoder og hvordan de fungerer
	- Symmetrisk
	- Asymmetrisk
	- Hashing
3. Anvendelser, krypto i lagmodellen
	- Applikasjonslag: Signering av dokumenter (PKI - Public Key Infrastructure)
	- Transportlag: Sikker kommunikasjon ende-til-ende (TLS - Transport Layer Security)
	- Nettverkslag: Sikker kommunikasjon mellom nett (VPN)
	- Lenkelag: Sikker kommunikasjon mellom tilstøtende noder (WPA2)
### Kryptografiske metoder
1. Symmetrisk
	- Fra (militærets) tidligere morgen (Cæsar, Enigma)
	- En felles nøkkel (kodemetode), kjent av begge parter
	- Standard: AES (Advanced Encryption Standard). Metoden er kjent, nøkkelen hemmelig
	- Fordel effektiv bruk av CPU
2. Asymmetrisk
	- To nøkler, en privat og en offentlig
	- Det som krytere med den ene nøkkelen kan bare dekrypteres med den andre.
	- Standarden RSA (Rivest-Shamir-Adleman) er grunnlaget for PKI og digitale sertifikater
	- Fordel: Enkelt distribuere offentlig nøkkel som motparten bruker til kryptering
	- Ulempe: Krevende CPU-belastning
3. Hashing
	- Beregner en sjekksum, et digital fingeravtrykk, av melding
	- Sjekksummen har en fast lengde og kan ikke brukes "i revers" for å finne meldingen. Enhver endring i meldingen git totalt annerledes sjekksum
	- Standarden som brukes heter SHA, Secure Hashing Algorithm

### Anvendelser av kryptometoder
Vi har de tre krypto-metodene:
- Symmetrisk, asymmetrisk og hashing
Som gir de tre sikkerhetsfunksjonene:
- Confidentiality, integrity and authenticity (CIA)
**Anvendelser** av sikkerhetsfunksjonene finner vi på ulike lag i TCP/IP-modellen. De fungerer uavhengige av hverandre, dvs alle metodene kan brukes ssamtidig om man er koblet opp slik.
- Applikasjonslaget: Signering (autentisert epost, sertifikat)
- Transportlaget: TLS/SSL(Digitale sertifikater, PKI)
- Nettverkslaget: VPN (IPSec - virtuelle private nett)
- Lenkelaget: WPA (Kryptert trådløst)
- 

