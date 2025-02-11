Alle subnett er definert av et prefiks: a.b.c.0/24 der i dette tilfellet er prefikset a, b og c med 256 adresser da det er $32- 24 =8$ tilgjengelige bits og dermed $2^8 = 256$ unike variasjoner der 0 endres til ulike verdier.  /25 har 128 adresser, /26 har 64 adresser osv.

### ARP - Address resolution protocol
Spør hvilken MAC-adresse har en gitt IP adressen, fortell så svaret til en spesifisert IP adresse.

**KOMMER PÅ EKSAMEN!!**
### Ruting
Rutere bygger opp en rutingtabell som sier hvilke utganger (interfaces) som IP-pakker må sendes ut på for å komme til en bestemt destinasjon
- Direkte tilkoblet subnett legges inn i tabellen automatisk. Her er rutererns interface en node i det tilkoblede subnettet
- Fjerntliggende destinasjoner kan legges inn manuelt som statisk rutere, eller som dynamiske ruter generert av ruting protokoller