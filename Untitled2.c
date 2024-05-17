#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int numeroUsuarios;
    float anchoBandaCanal;
    float anchoBandaGuarda;
    float frecuenciaCentralCanal1;
} DatosMultiplexacion;

void solicitarDatos(DatosMultiplexacion *datos) {
    do {
        printf("Ingrese el número de usuarios: ");
        scanf("%d", &datos->numeroUsuarios);
    } while (datos->numeroUsuarios <= 0);

    do {
        printf("Ingrese el ancho de banda de cada canal (en kHz): ");
        scanf("%f", &datos->anchoBandaCanal);
    } while (datos->anchoBandaCanal <= 0);

    do {
        printf("Ingrese el ancho de banda de la guarda (en kHz): ");
        scanf("%f", &datos->anchoBandaGuarda);
    } while (datos->anchoBandaGuarda <= 0);

    printf("Ingrese la frecuencia central del canal 1 (en MHz): ");
    scanf("%f", &datos->frecuenciaCentralCanal1);
}

void calcularFrecuenciaPortadoraUsuario(DatosMultiplexacion datos, int numeroUsuario, float *frecuenciaPortadora) {
    *frecuenciaPortadora = datos.frecuenciaCentralCanal1 + (numeroUsuario - 1) * (datos.anchoBandaCanal + datos.anchoBandaGuarda) / 1000.0f;
}

float calcularAnchoBandaTotal(DatosMultiplexacion datos) {
    return 2 * (datos.anchoBandaCanal / 2) + (datos.numeroUsuarios - 1) * (datos.anchoBandaCanal + datos.anchoBandaGuarda);
}

float calcularTasaKbpsUsuario() {
    return 100.0f; // Tasa fija de transmisión por usuario en kbps
}

float calcularTasaKbpsTotal(DatosMultiplexacion datos) {
    return datos.numeroUsuarios * calcularTasaKbpsUsuario();
}

float calcularTasaKbpsTotalSinGuarda(float anchoBandaTotal) {
    return anchoBandaTotal * 0.5f; // Utilizando toda la banda, relación 0.5 bps/Hz
}

void imprimirResultados(DatosMultiplexacion datos, float anchoBandaTotal, float tasaKbpsTotal, float tasaKbpsTotalSinGuarda) {
	int i;
    for (i = 1; i <= datos.numeroUsuarios; i++) {
        float frecuenciaPortadoraUsuarioActual;
        calcularFrecuenciaPortadoraUsuario(datos, i, &frecuenciaPortadoraUsuarioActual);
        printf("Frecuencia portadora del usuario %d: %.6f MHz\n", i, frecuenciaPortadoraUsuarioActual);
    }

    printf("Ancho de banda total: %.2f kHz\n", anchoBandaTotal);
    printf("Número total de Kbps que se transmiten: %.2f kbps\n", tasaKbpsTotal);
    printf("Número total de Kbps que podrían transmitirse utilizando todo el ancho de banda: %.2f kbps\n", tasaKbpsTotalSinGuarda);
}

int main() {
    DatosMultiplexacion datos;

    solicitarDatos(&datos);

    float anchoBandaTotal = calcularAnchoBandaTotal(datos);
    float tasaKbpsTotal = calcularTasaKbpsTotal(datos);
    float tasaKbpsTotalSinGuarda = calcularTasaKbpsTotalSinGuarda(anchoBandaTotal);

    imprimirResultados(datos, anchoBandaTotal, tasaKbpsTotal, tasaKbpsTotalSinGuarda);

    return 0;
}

