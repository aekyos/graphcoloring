#include <stdio.h>
#include <stdlib.h>
#include "../veinteveinte.h"

static void ordenar(Grafo G){
    for (u32 i = 0; i < NumeroDeVertices(G); i++) {
        FijarOrden(i,G,i);
    }
}
//---------------funciones check------------------
void check_WP(Grafo g) {
    // El primer vértice lo contamos por afuera.
    u32 prev_gr = Grado(0, g);
    u32 curr_gr;
    for (u32 i = 1; i < NumeroDeVertices(g); i++) {
        curr_gr = Grado(i, g);
        if (curr_gr>prev_gr){
            printf("ERROR en WelshPowell\n");
        }
        prev_gr = curr_gr;
    }
}

void check_RevierteBC(Grafo g){
    // El primer vértice lo contamos por afuera.
    u32 prev_clr = Color(0, g);
    u32 curr_clr;
    for (u32 i = 1; i < NumeroDeVertices(g); i++) {
        curr_clr = Color(i, g);
        if (curr_clr>prev_clr){
            printf("ERROR en RevierteBC\n");
        }else if(curr_clr + 1 < prev_clr)
            printf("ERROR -RARO- en RevierteBC\n");
        prev_clr = curr_clr;
    }
}

void check_ChicograndeBC(Grafo G) {
  // El primer vértice lo contamos por afuera.
    u32 colour = Color(0, G);
    u32 prev_cnt = 0;
    u32 curr_cnt = 1;
    for (u32 i = 1; i < NumeroDeVertices(G); i++) {
        if (Color(i, G) == colour) {
            // Encontramos un vértice con color colour.
            curr_cnt++;
        } else {
            // Llegamos al siguiente BC.
            // Si hay más vertices en el BC anterior, está mal ordenado.
            if (prev_cnt > curr_cnt)
                printf("ERROR en ChicoGrandeBC\n");
                // Empezamos a contar de nuevo.
            prev_cnt = curr_cnt;
            curr_cnt = 1;
            colour = Color(i, G);
        }
    }
    if (prev_cnt > curr_cnt)
        printf("ERROR en ChicoGrandeBC\n");
}

void check_aleatorizar(Grafo g) {
    u32 check;
    u32 n;
    for (u32 i = 0; i < NumeroDeVertices(g); i++) {
        check = 0;
        n = Nombre(i, g);
        for (u32 j = 0; j < NumeroDeVertices(g); j++) {
            if( n == Nombre(j, g)){
                check++;
            }
        }
        if (check != 1){
            printf("ERROR en Aleatorizar\n");
        }
    }
}

void coloreoPropio2(Grafo g){
    u32 vertices =NumeroDeVertices(g);
    for(u32 i = 0; i < vertices; i++){
        u32 grado = Grado(i, g);
        u32 icolor = Color(i, g);
        for(u32 j = 0; j < grado; j++){
            if(icolor == ColorVecino(j, i, g)){
                printf("--------ERROR: COLOREO NO PROPIO--------\n");
            }
        }
    }
    printf("--------OK: COLOREO PROPIO--------\n");
}

//----------------COMPONENTES-CONEXAS-------------
void comcon(Grafo g){
    // printf("testeando componentes conexas\n");
    u32 num = NumCCs(g);
    printf("Componentes conexas: %u\n", num);
}


//---------------------BIPARTITO---------------------
u32 testBipartitoWelsh(Grafo g){
    // printf("Test bipartito con WP\n");
    ordenar(g);
    u32 b = Bipartito(g);
    if(b){
        printf("es bipartito\n");
    }else{
        printf("NO es bipartito\n");
    }
    if (WelshPowell(g)){
        printf("ERROR: Haciendo Welshpowell\n");
        return 1;
    }
    u32 bw = Bipartito(g);
    if(b==bw){
        return 0;
    }else{
        printf("ERROR: Bipartito con Welshpowell\n");
        return 1;
    }
}

//----------------------COLOREO-------------------
void ordenColor(Grafo g){
    u32 aux = Greedy(g);
    for (u32 i = 0; i < 10; i++)
    {
        RevierteBC(g);
        u32 aux1 = Greedy(g);
        if(aux1 > aux){
            printf("---ERROR: COLOREO MAYOR DESPUES DE REORDEN DE COLORES\n");
            coloreoPropio2(g);
        }
        aux = aux1;
    }
    printf("cantidad de colores: %u\n", aux);
}


void chicograndeMil(Grafo g){
    Greedy(g);
    for (u32 i = 1; i < 1000; i++)
    {   ChicoGrandeBC(g);
        Greedy(g);
    }
}

void chicograndeCien(Grafo g){
    Greedy(g);
    for (u32 i = 1; i < 100; i++)
    {   ChicoGrandeBC(g);
        Greedy(g);
    }
}
void revierteMil(Grafo g){
    Greedy(g);
    for (u32 i = 1; i < 1000; i++)
    {   RevierteBC(g);
        Greedy(g);
    }
}

void revierteCien(Grafo g){
    Greedy(g);
    for (u32 i = 1; i < 100; i++)
    {   RevierteBC(g);
        Greedy(g);
    }
}

void reviertef(Grafo g){
    Greedy(g);
    for (u32 i = 1; i < 50; i++)
    {   RevierteBC(g);
        Greedy(g);
    }
}

//-------------ALEATORIZAR-------------------
void aleatorizarMil(Grafo g){
    Greedy(g);
    for (u32 i = 1; i < 1000; i++)
    {
        AleatorizarVertices(g,i);
        Greedy(g);
    }
}

void aleatorizarCien(Grafo g){
    Greedy(g);
    for (u32 i = 1; i < 100; i++)
    {
        AleatorizarVertices(g,i);
        Greedy(g);
    }
}
//------------------WP-----------------------

void wpMil(Grafo g){
    Greedy(g);
    for (u32 i = 1; i < 1000; i++)
    {
        WelshPowell(g);
        Greedy(g);
    }
}

void wpCien(Grafo g){
    Greedy(g);
    for (u32 i = 1; i < 100; i++)
    {
        WelshPowell(g);
        Greedy(g);
    }
}

void wpDiez(Grafo g){
    Greedy(g);
    for (u32 i = 1; i < 10; i++)
    {
        WelshPowell(g);
        Greedy(g);
    }
}

void greedy_N_WP(Grafo g){
    ordenar(g);
    u32 res = Greedy(g);
    printf("greedy natural:%d\n", res);
    WelshPowell(g);
    u32 res1 = Greedy(g);
        printf("greedy WP:%d\n", res1);
    if (res > res1){
        printf("Greedy WP mejor\n");
    }else if(res1 > res){
        printf("Greedy N mejor\n");
    }else{
        printf("IGUALES\n");
    }
}

void chequeototal(Grafo g){
    Greedy(g);
    coloreoPropio2(g);

    testBipartitoWelsh(g);
    coloreoPropio2(g);


    WelshPowell(g);
    check_WP(g);
    Greedy(g);
    coloreoPropio2(g);

    RevierteBC(g);
    check_RevierteBC(g);
    Greedy(g);
    coloreoPropio2(g);

    ChicoGrandeBC(g);
    check_ChicograndeBC(g);
    Greedy(g);
    coloreoPropio2(g);

    // printf("c hequeando aleatorizar, puede tardar por ser n^2\n");
    AleatorizarVertices(g, 1);
    check_aleatorizar(g);
    Greedy(g);
    coloreoPropio2(g);

    comcon(g);

    ordenColor(g);
    coloreoPropio2(g);
    printf("\n\n");
}
void imprimir(Grafo g){
    for(u32 i = 0; i<NumeroDeVertices(g);i++){
        printf("%d-",Nombre(i,g));
    }
}

//------------------------------------------------------------------
//------------------------------MAIN--------------------------------
//------------------------------------------------------------------
int main(){
    Grafo g = ConstruccionDelGrafo();

    // testBipartitoWelsh(g);
    chequeototal(g);
    comcon(g);

    DestruccionDelGrafo(g);
    return(0);
}
