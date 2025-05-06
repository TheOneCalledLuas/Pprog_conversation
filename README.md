# PProg_conversation 
UAM PProg proyect 2024/25


Por Saúl López Romero, Fernando Mijangos, Irene García y Raquel Anguita.
Esto es un proyecto de programación en C para el curso 2024/25.

Estructura del respositorio:
    .c en /src
    .o en /obj
    .dat en /data
    .a en /lib
    .h en /include
    

I3: Hecho.
https://docs.google.com/document/d/1GAtCxuzERH6r5lT3FtsnwfeleTyBKrgcXXioH0YLOgI/edit?usp=sharing


gamerules por hacer:

- cuando se usa el ticket (id o13) en la habitación del antrain (id o27) ambos jugadores pierden todos los objetos y se curan y se mueven automáticamente a la habitación id s112 (cuando lo hagas me avisas para eliminar la habitación tutorial id s111)
- después de hablar con la hormiga en la habitación id s711 id c62, hay que comprobar tras matar a la reina araña (id c60) si todas las arañas han muerto (ids c63, c64, c67, c69) en cuyo caso se desbloquea el final malo. el final malo implica que después de matar a merchAnt hay una cutscene de las hormigas felicitando a los jugadores y luego estos discutiendo por el poder del homiguero antes de que unas arañas lleguen en busca de venganza y las maten. (se puede acortatr la cutscene es sólo como algo así de final malo para que se vea que al final matar bebés no lleva a ninguna parte)
- tras hablar con la hormiga en la habitación id s121 (id c65) hay cuatro turnos (por jugador) para llegar hasta las dos palancas y usarlas para poder abrir los links ids l411 (lever 1) y l451 (lever 2) y así poder llegar a salvar a la bebé hormiga a tiempo. sino, id c66 muere tras el cuarto turno del último jugador (aun se pueden desbloquear los links).
- matar a la reinaraña (id c60) desbloquea el camino a la habitación 0 (id l310) y lleva a los jugadores a la habitación id s113 y bloquea el camino de vuelta id l301
- cuando se usa el objeto id o213 se desbloquea el link id l491 y el objeto de id o216 se vuelve inamovible. si algun jugador lo tiene en el inventario, se le cae en la habitación en la que estén (obligatoriamente id s131) y no pueden volver a cogerlo. la hormiga de id c68 desaparece.
- si se usa la dinamita (id o216) en la habitació id s131 antes de que el link id l310 esté abierto, el link se abre y la hormiga encerrada id c70 muere y la de c68 desaparece.
- si se usa el objeto de id o212 se consigue un boost de ataque de +1 (permanente o exclusivamente contra la reinaraña id c60, lo que sea más fácil). si no, simplemente ignora este gamerule y cambia para que de como 5 de vida o algo, este es el menos importante de los gamerules.
