# Darius-Florentin Neatu <neatudarius@gmail.com>

# Exemplu de Makefile pentru tema

# tag-uri obligatorii (nume + comportament identic)
# build    => compileaza toata tema
#             (ATENTIE! E important - NU compilati in tag-urile de run. Sesizati?)
# run-p$ID => ruleaza problema cu ID-ul specificat (1, 2, 3, 4)
# clean    => sterge toate fisierele generate

# restul este la alegerea studentului
# TODO

# nume necesar (build)
build: project
	javac project/*.java
	jar cf PA.jar project/*.class

run-p1:      # nume necesar
	java -classpath ./PA.jar project.Crypto
run-p2:      # nume necesar
	java -classpath ./PA.jar project.Stocks
run-p3:      # nume necesar
	java -classpath ./PA.jar project.Valley
run-p4:      # nume necesar
	java -classpath ./PA.jar project.Ridge
clean:		 # nume necesar
	rm project/*.class
	rm PA.jar