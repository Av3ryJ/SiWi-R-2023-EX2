# Red-Black-Gauss-Seidel
### Aufruf
Aufruf ./rbgs nx ny c th
mit nx= Anzahl der Intervalle in x-Richtung
    ny= Anzahl der Intervalle in y-Richtung
    c= Anzahl der Iterationen 
    th= Anzahl der Threads für OpenMp Parallelisierunng --> ist optional, wenn keine Threadanzahl übergeben wird, nimmt der Compiler zur Berechnung automatisch alle Threads,die ihm zur Verfügung stehen 


Es entsteht eine Ausgabe Datei solution.txt, in der die jeweiligen Werte für jede Stelle (x,y) in der Matrix stehen und auf der Kommandozeile sieht man zum einen die Laufzeit der Berechnung in Sekunden und die L2 Norm des Residuums


