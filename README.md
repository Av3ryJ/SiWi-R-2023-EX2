# Red-Black-Gauss-Seidel
### Aufruf
Aufruf ./rbgs nx ny c th
mit nx= Anzahl der Intervalle in x-Richtung
    ny= Anzahl der Intervalle in y-Richtung
    c= Anzahl der Iterationen 
    th= Anzahl der Threads für OpenMp Parallelisierunng --> ist optional, wenn keine Threadanzahl übergeben wird, nimmt der Compiler zur Berechnung automatisch alle Threads,die ihm zur Verfügung stehen 

### ACHTUNG 
nx und ny entsprechen der Anzahl der Intervalle, das Gitter hat also (nx+1) Punkte in x-Richtung und (ny+1) Punkte in y-Richtung. Insgesamt besteht das Gitter also aus (nx+1)*(ny+1) Punkten, wobei die jeweils äußersten Punkte als Rand betrachtet werden, also vor der Berechnung durch die Aufgabenstellung festgelegt sind und während der Rechnung nicht verändert werden. 

### Ausgabe
Es entsteht eine Ausgabe Datei solution.txt, in der die jeweiligen Lösungswerte für jede Stelle (x,y) des Gitters stehen. Das Gitter kann mit der splot Funktion von gnuplot visualisiert werden.
Auf der Kommandozeile wird zum einen die Laufzeit der Berechnung in Sekunden und zum anderen die L2 Norm des Residuums ausgegeben.