COPT = -Wall -ggdb

orders: main.c io.o simplex.o table.o
	$(CC) $(COPT) -o orders main.c io.o simplex.o table.o

simplex.o: simplex.h simplex.c
	$(CC) $(COPT) -c simplex.c

io.o: io.h io.c
	$(CC) $(COPT) -c io.c

table.o: table.h table.c
	$(CC) $(COPT) -c table.c

.PHONY: clean input output

clean:
	-rm *.o
	-rm orders

input:
	./orders
	./orders -a 1234
	./orders -i abc
	./orders -i tjhdujernr -o def
	./orders -i test/input/t0-pusty_plik_wejscinputwy.txt -o a
	./orders -i test/input/t1-brak_id_apteki.txt -o a
	./orders -i test/input/t2-brak_nazwy_apteki.txt -o a
	./orders -i test/input/t3-brak_dziennej_produkcji.txt -o a
	./orders -i test/input/t4-brak_id_producenta.txt -o a
	./orders -i test/input/t5-brak_nazwy_producenta.txt -o a
	./orders -i test/input/t6-brak_dziennego_zapotrzebowania.txt -o a
	./orders -i test/input/t7-brak_id_producenta_polaczenia.txt -o a
	./orders -i test/input/t8-brak_id_apteki_polaczenia.txt -o a
	./orders -i test/input/t9-brak_dziennej_maksymalnej_liczby_dostarczanych_szczepionek.txt -o a
	./orders -i test/input/t10-brak_kosztu_szczepinputnki.txt -o a
	./orders -i test/input/t11-brak_apteki.txt -o a
	./orders -i test/input/t12-brak_poducenta.txt -o a
	./orders -i test/input/t13-brak_polaczenia.txt -o a
	./orders -i test/input/t14-brak_komentarza_pierwszego.txt -o a
	./orders -i test/input/t15-brak_komentarza_drugiego.txt -o a
	./orders -i test/input/t16-brak_komentarza_trzeciego.txt -o a
	./orders -i test/input/t17-brak_danych.txt -o a
	./orders -i test/input/t18-zduplikowane_id_producenta.txt -o a
	./orders -i test/input/t19-zduplikowane_id_apteki.txt -o a
	./orders -i test/input/t20-zduplikowane_id_polaczenia.txt -o a
	./orders -i test/input/t21-id_nieistniejacego_producenta.txt -o a
	./orders -i test/input/t22-id_nieistniejacej_apteki.txt -o a
	./orders -i test/input/t23-id_nieistniejacego_producenta_polaczenia.txt -o a
	./orders -i test/input/t24-id_nieistniejacej_apteki_polaczenia.txt -o a
	./orders -i test/input/t25-ujemna_dzienna_produkcja.txt -o a
	./orders -i test/input/t26-ujemne_dzienne_zapotrzebowanie.txt -o a
	./orders -i test/input/t27-ujemne_id_producenta.txt -o a
	./orders -i test/input/t28-ujemne_id_apteki.txt -o a
	./orders -i test/input/t29-ujemne_id_producenta_polaczenia.txt -o a
	./orders -i test/input/t30-ujemne_id_apteki_polaczenia.txt -o a
	./orders -i test/input/t31-t31-ujemna_dzienna_maksymalna_liczba_dostarczanych_szczepionek.txt -o a
	./orders -i test/input/t32-ujemny_koszt.txt -o a
	./orders -i test/input/t33-poprawne_dane_wejscinputwe.txt -o a
output:
	./orders -i test/output/data_in/d1-prawidlowe_dane.txt  -o test/output/data_out/d1-prawidlowe_dane.txt
	./orders -i test/output/data_in/d2-za_malo_szczepionek.txt  -o test/output/data_out/d2-za_malo_szczepionek.txt
	./orders -i test/output/data_in/d3-rowna_ilosc_szczepionek.txt  -o test/output/data_out/d3-rowna_ilosc_szczepionek.txt
	./orders -i test/output/data_in/d4-rowna_ilosc_szczepionek_losowe.txt  -o test/output/data_out/d4-rowna_ilosc_szczepionek_losowe.txt
	./orders -i test/output/data_in/d5-dane_losowe_10x100.txt  -o test/output/data_out/d5-dane_losowe_10x100.txt
	./orders -i test/output/data_in/d6-dane_losowe_25x25.txt  -o test/output/data_out/d6-dane_losowe_25x25.txt
	./orders -i test/output/data_in/d7-dane_losowe_50x50.txt -o test/output/data_out/d7-dane_losowe_50x50.txt
	./test/output/result_test test/output/data_in/d1-prawidlowe_dane.txt test/output/data_out/d1-prawidlowe_dane.txt
	./test/output/result_test test/output/data_in/d3-rowna_ilosc_szczepionek.txt test/output/data_out/d3-rowna_ilosc_szczepionek.txt
	./test/output/result_test test/output/data_in/d4-rowna_ilosc_szczepionek_losowe.txt test/output/data_out/d4-rowna_ilosc_szczepionek_losowe.txt
	./test/output/result_test test/output/data_in/d5-dane_losowe_10x100.txt test/output/data_out/d5-dane_losowe_10x100.txt
	./test/output/result_test test/output/data_in/d6-dane_losowe_25x25.txt test/output/data_out/d6-dane_losowe_25x25.txt
	./test/output/result_test test/output/data_in/d7-dane_losowe_50x50.txt  test/output/data_out/d7-dane_losowe_50x50.txt