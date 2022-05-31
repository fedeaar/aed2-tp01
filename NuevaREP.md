Nueva rep SimCity? AvanzarTurno O(1)

SimCity se representa con estr
    donde estr es tupla(antiguedad : Nat,
                        turno : Nat,
                        popularidad : Nat,
                        mapa : Mapa,
                        construcciones : listaLineal(tupla<turnoAgregado: Nat, 
                                                           construs: puntero(diccLineal(pos, Construccion))>),
                        uniones : lista(hijo) )

    donde hijo es tupla(sc : puntero(estr) ,
                        turnoUnido : Nat )
                        
    donde pos es tupla(x : Nat , y : Nat )

Para conocer casas, necesito tambien un aux donde paso por parametro una variable que acumula los comercios hasta ese nodo 
(ya que no se pueden solapar casas con nodos hacia arriba ni izquierda). 

Pseudocodigo
    Base: Agrega casas de padre y almacena comercios 
    Recursivo: Agrega casas sii no estan en res ni en comercios almacenados
               Almacena sus comercios

Para conocer comercios, necesito lo mismo, pero aparte, guardarme el resultado de la funcion casas para calcular el nivel 
(es recorrer) todas las casas y ver el nivel mas alto de la de manhattan <= 3 o el del comercio de base.

Pseudocodigo
    Base: Agrega casas de padre y almacena comercios 
    Recursivo: Agrega casas sii no estan en res ni en comercios almacenados
               Almacena sus comercios

               (Nivel se calcula con los dos casos)


Para calcular nivel, 

1: Este en padre: turno - turnoAgregado
2: Union: turno - turnoUnido + 

nivel:
    Base: 1 me pregunto por constru del padre
    Recursivo: 2  me pregunto por constru de otro nodo hijo    