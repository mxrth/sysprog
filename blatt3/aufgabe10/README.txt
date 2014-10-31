Aufgabe 10

(a) Ein Server stellt Dienste bereit, die ein Client anfordern kann, indem 
    er einen Request an den Server schickt.
    Der Server wartet auf einen Verbindungsaufbauwunsch.
    Der Client initiiert den Verbindungsaufbau.

(b) Die IP-Adresse identifiziert den Rechner auf dem der Prozess läuft 
    und die Portnummer den Prozess.

(c) TCP arbeitet verbindungsorientiert, daher muss zunächst die Verbindung
    hergestellt werden. Die Verbindung ermöglicht die full-duplex Datenüber-
    tragung und dadurch können Antworten geschickt werden.
    Das Transportprotokoll ist größer als bei UDP => Es müssen mehr Daten 
    gesendet werden. 
    Möchte der Entwickler eine große Menge an Daten möglichst schnell 
    senden und ist die Korrektheit der Daten nicht so wichtig, so ist UDP 
    die bessere Wahl.
