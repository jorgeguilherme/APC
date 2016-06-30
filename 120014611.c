# include <stdio.h>
# include <ctype.h>
# include <math.h>
# include <stdlib.h>
/*

Algoritmos e Programação de Computadores
Jorge Guilherme Silva dos Santos - 12/0014611
contato@jorgeguilherme.eng.br

ctype.h e necessario para uso do toUpper nas verificacoes que exigem um caractere como entrada do usuario
   math.h   e necessario para uso de sqrt e pow
     stdlib.h para comando system usado para limpar tela.
     ISSO FAZ O CODIGO NAO SER PORTAVEL PARA WINDOWS!!!

Continuacao do primeiro trabalho, aproveitando todo o codigo do mesmo e adicionando
novas funcionalidades. Optei por nao fazer a refatoracao. */



/* Registro da nave */

typedef struct {
    char nome[20];
    int contadorRodadas;
    int combustivel;
    int numMotores;
    int integridadeCasco;
    int rodadasRaioDaMorte;                    /* Rodadas DESDE QUE foi utilizado a ultima vez */
    int contadorMeteoroPegasus;                /* Salva numero de vezes que foi utilizado */
    int contadorTempestadeLerigou;  /* Salva numero de vezes que foi utilizado */
    int energia;
    int energiaBloqueada;
    int contadorProtegoMaxima;            /* Salva numero de vezes que foi utilizado */
    int contadorRepelloInimigotum;    /* Salva numero de vezes que foi utilizado */
    int posX;
    int posY;
} nave;

void start_SimGene(FILE*, char*, char*, int*);
void CompletaFitasDNA (char*, char*);
int BuscaStringEmString (char*, char*);
void TheGreatEscape (nave*, nave*);
void CopiaStrings (char*, char*, int);
int LeiaMapa (char*, int, int);
void LimpaTela();
int TamanhoString (char*);
void ExibeMapa (char*,int, int);
void PosicionaNave (char*, int, int, char, nave*);
void IniciarFugaTenente(nave*, nave*, char*, int, int, int);
void BatalhaComoFlame(nave*, nave*, char*, int, int, int);
int MovimentaNave (nave*, char*, char, int);
void ExibeStatus (nave*, nave*, char*);
int IniciarBatalha (nave*, nave*, char*, char*, int, int);
int EscolhaArmamento ();

int main () {


    char    caractereBoasVindas;
    int     opcaoSelecionadaMenu;
    float    coordenadaAtualEixoX = 0.0;
    float     coordenadaAtualEixoY = 0.0;
    float     coordenadaAtualEixoZ = 0.0;
    float    gravidadeLocal = 0.0;
    int     numeroMotores = 0;
    float     quantidadeCombustivel = 0.0;
    float    eficienciaMotores = 0.0;
    const float        coordenadaOyaEixoX = 208.0;
    const float     coordenadaOyaEixoY = 340.0;
    const float     coordenadaOyaEixoZ = 234.0;
    const float        pesoMotor = 15.0;
    const float        rendimentoNormal = 5.0;
    const float        pesoNave = 14000.0;
    float    distanciaMaxima = 0.0;
    float     rendimentoHiperEspaco = 0.0;
    float    massaNaveTotal = 0.0;
    float    distanciaPercorrer = 0.0;
    char    continuarViagem;
    FILE *arquivoAmostra;
    char fitaDNA1[1100];            /* Existe um certo exagero no tamanho do vetor */
    char fitaDNA2[1100];            /* Existe um certo exagero no tamanho do vetor */
    char nomeArquivo[100];
    int pilotoAutomatico = 0;    /* Piloto autom. desativado por padrao */


    /* Criação da nave */
    /* Sera passada como parametro para a parte da batalha
    Entendi que e melhor manter o status das duas naves com os dois jogadores
    para facilitar debug e as jogadas.
    As informacoes das duas naves poderao ser salvas nos arquivos binarios
    para criacao posterior do replay*/
    nave EM;
    nave D;

    /* Tela de boas vindas */

    printf("**********************************************************************\n");
    printf("**********************************************************************\n");
    printf("******************************          ******************************\n");
    printf("*****************************  WARARRAY  *****************************\n");
    printf("******************************          ******************************\n");
    printf("**********************************************************************\n");
    printf("**********************************************************************\n");
    printf("**************************                  **************************\n");
    printf("******************** Nobre usuario, seja bem vindo *******************\n");
    printf("********************* Pressione W para continuar *********************\n");
    printf("**************************                  **************************\n");
    printf("**********************************************************************\n");
    printf("**********************************************************************\n");


    /* Le tecla do usuario ate duas vezes. A partir da segunda vez, o programa e encerrado por nao ser pressionada a tecla valida
    (apenas a tecla W) e valida na tela de boas vindas
    A escolha de quantas tentativas possiveis sao permitidas e determinacao do roteiro */

    scanf("%c", &caractereBoasVindas); getchar();

    if ( toupper(caractereBoasVindas) != 'W' ) {
        printf("Tecla nao valida foi pressionada. Pressione W para acessar o menu de escolhas  ");
        scanf("%c", &caractereBoasVindas); getchar();

        if ( toupper(caractereBoasVindas) != 'W' ) {

            /* Sai na segunda vez em que uma tecla errada foi pressionada */

            printf("\nTecla nao valida foi pressionada.");
            printf("\nSaindo...");
            getchar();
            return 0;
        }

    }

    /* Menu principal */
    /* Atualizacao em relacao a ultima versao:
    Criacao das opcoes 5 e 6 */
    printf("**********************************************************************\n");
    printf("**********************************************************************\n");
    printf("******************************          ******************************\n");
    printf("*****************************  WARARRAY  *****************************\n");
    printf("******************************          ******************************\n");
    printf("**********************************************************************\n");
    printf("*************************** MENU PRINCIPAL ***************************\n");
    printf("**********************************************************************\n");
    printf("***************** 1 Calculo do salto em hiperespaco  *****************\n");
    printf("******************* 2 SimGene (Simulador Genetico) *******************\n");
    printf("********************** 3 Escolha de modo de voo **********************\n");
    printf("******************** 4 Warraray, faca o que quiser *******************\n");
    printf("************************** 5 The Great Escape ************************\n");
    printf("****************************** 6 Replay ******************************\n");
    printf("**********************************************************************\n");
    printf("**********************************************************************\n");


    /* Le tecla do usuario ate duas vezes. A partir da segunda vez, o programa e encerrado por nao ser pressionada a tecla valida
    A escolha de quantas tentativas possiveis sao permitidas e determinacao do roteiro */


    scanf("%d", &opcaoSelecionadaMenu); getchar();

    if (opcaoSelecionadaMenu < 1 || opcaoSelecionadaMenu > 6) {

        printf("Tecla nao valida foi pressionada. Selecione a opcao usando um numero INTEIRO de 1 a 6  ");
        scanf("%d", &opcaoSelecionadaMenu); getchar();

            if (opcaoSelecionadaMenu < 1 || opcaoSelecionadaMenu > 4) {

                /* Sai na segunda vez em que uma tecla errada foi pressionada */

                printf("\nTecla nao valida foi pressionada pela segunda vez seguida, Saindo...\n");
                getchar();
                return 0;
            }

    }

    if (opcaoSelecionadaMenu == 1) {

        /* Opcao que efetua os calculos de acordo com os dados informados pelos usuario.
        Os eventos devem ser registrados no bordo */

        printf("Chefe, preciso das suas coordenadas atuais para efetuar esse calculo\n");
        printf("As coordenadas sao representadas em um espaco tridimensional, nos eixos x,y,z\n");
        printf("O centro de controle representa o ponto (0,0,0) e e portanto a referencia para toda a navegacao\n");

        /* Uma verificacao por coordenada, dessa vez o usuario precisa interagir menos antes de perceber que algo esta errado */

        /* Le entrada  do usuario ate duas vezes. A partir da segunda vez, o programa e encerrado por nao ter recebido uma entrada valida
        A escolha de quantas tentativas possiveis sao permitidas e determinacao do roteiro */
        printf("Por favor, entre com o valor da coordenada x: ");
        scanf("%f", &coordenadaAtualEixoX); getchar();

        if (coordenadaAtualEixoX <= 66 || coordenadaAtualEixoX >= 350) {

            printf("\nO valor da coordenada X digitado nao e valido. Sao permitidos valores de X entre 66 e 350. Tente novamente: ");
            scanf("%f", &coordenadaAtualEixoX); getchar();

            if (coordenadaAtualEixoX <= 66 || coordenadaAtualEixoX >= 350) {
                printf("\nO valor da coordenada X digitado nao e valido pela segunda vez seguida.\nSaindo...");
                getchar();
                return 0;
            }

        }

        /* Le entrada  do usuario ate duas vezes. A partir da segunda vez, o programa e encerrado por nao ter recebido uma entrada valida
        A escolha de quantas tentativas possiveis sao permitidas e determinacao do roteiro */
        printf("Por favor, entre com o valor da coordenada y: ");
        scanf("%f", &coordenadaAtualEixoY); getchar();

        if (coordenadaAtualEixoY <= 199 || coordenadaAtualEixoY >= 482) {

            printf("\nO valor da coordenada Y digitado nao e valido. Sao permitidos valores de Y entre 199 e 482. Tente novamente: ");
            scanf("%f", &coordenadaAtualEixoY); getchar();

            if (coordenadaAtualEixoY <= 199 || coordenadaAtualEixoY >= 482) {
                printf("\nO valor da coordenada Y digitado nao e valido pela segunda vez seguida.\nSaindo...");
                getchar();
                return 0;
            }

        }

        /* Le entrada  do usuario ate duas vezes. A partir da segunda vez, o programa e encerrado por nao ter recebido uma entrada valida
        A escolha de quantas tentativas possiveis sao permitidas e determinacao do roteiro */
        printf("Por favor, entre com o valor da coordenada z: ");
        scanf("%f", &coordenadaAtualEixoZ); getchar();

        if (coordenadaAtualEixoZ <= 93 || coordenadaAtualEixoZ >= 375) {

            printf("\nO valor da coordenada Z digitado nao e valido. Sao permitidos valores de X entre 93 e 375. Tente novamente: ");
            scanf("%f", &coordenadaAtualEixoZ); getchar();

            if (coordenadaAtualEixoZ <= 93 || coordenadaAtualEixoZ >= 375) {
                printf("\nO valor da coordenada Z digitado nao e valido pela segunda vez seguida.\nSaindo...");
                getchar();
                return 0;
            }

        }

        printf("\n Coordenadas atuais: (%f,%f,%f).\n", coordenadaAtualEixoX, coordenadaAtualEixoY, coordenadaAtualEixoZ);


        /* Le entrada  do usuario ate duas vezes. A partir da segunda vez, o programa e encerrado por nao ter recebido uma entrada valida
        A escolha de quantas tentativas possiveis sao permitidas e determinacao do roteiro */
        printf("\n\nAgora, preciso do valor da gravidade no local, em Graitons. Em caso de duvidas, consulte o diario de bordo, essas informacoes devem ser registradas la\n");
        scanf("%f", &gravidadeLocal); getchar();

        if ( gravidadeLocal < 1 || gravidadeLocal > 20) {

            printf("\nO valor da gravidade local nao estar fora do intervalo [1..20]. Tente novamente: ");
            scanf("%f", &gravidadeLocal); getchar();

            if ( gravidadeLocal < 1 || gravidadeLocal > 20) {

                printf("O valor de gravidade foi incorretamente digitado pela segunda vez seguida. \n Saindo...");
                getchar();
                return 0;
            }
        }

        /* Le entrada  do usuario ate duas vezes. A partir da segunda vez, o programa e encerrado por nao ter recebido uma entrada valida
        A escolha de quantas tentativas possiveis sao permitidas e determinacao do roteiro */
        printf("\n\nDessa vez, preciso da quantidfade de motores na sua nave. Quantos são?");
        scanf("%d", &numeroMotores); getchar();

        if ( numeroMotores < 0 || numeroMotores > 8) {

            printf("\n\nO valor do numero de motores nao pode ser negativo e nem maior que oito. Tente novamente: ");
            scanf("%d", &numeroMotores); getchar();

            if ( numeroMotores < 0 || numeroMotores > 8) {

                printf("O valor do numero de motores incorretamente digitado pela segunda vez seguida. \n Saindo...");
                getchar();
                return 0;
            }
        }

        /* Le entrada  do usuario ate duas vezes. A partir da segunda vez, o programa e encerrado por nao ter recebido uma entrada valida
        A escolha de quantas tentativas possiveis sao permitidas e determinacao do roteiro */
        printf("\n\nAgora, observe o painel da nave. Leia e entre com a quantidade de combustivel disponivel, em Combustons: ");
        scanf("%f", &quantidadeCombustivel); getchar();

        /* Cada motor pode armazenar ate 50 Combustons. Dessa forma, a quantidade lida nao pode ser maior que a quantidade de motores
        multiplicada pela capacidade do tanque de cada um deles */
        if ( quantidadeCombustivel < 0.0 || quantidadeCombustivel > numeroMotores*50.0 ) {

            printf("\nO valor do combustivel parece incorreto. Note que esse valor nao pode ser negativo e nem ser superior a capacidade somada dos tanques de cada motor.\nTente novamente: ");
            scanf("%f", &quantidadeCombustivel); getchar();

            if ( quantidadeCombustivel < 0.0 || quantidadeCombustivel > numeroMotores*50.0 ) {

                printf("O valor da quantidade de combustivel foi digitado incorretamente pela segunda vez seguida. \n Saindo...");
                getchar();
                return 0;
            }

        }

        /* Le entrada  do usuario ate duas vezes. A partir da segunda vez, o programa e encerrado por nao ter recebido uma entrada valida
        A escolha de quantas tentativas possiveis sao permitidas e determinacao do roteiro */
        printf("\n\nVamos precisar de informacoes sobre os motores. Consulte o diario de bordo para verificar quanto da eficiencia do motor restou.\n");
        printf("Devo lembrar que os Unitron 3000 vem de fabrica com eficiencia inicial de 90 porcento.\n");
        printf("Entre com o valor (real) da eficiencia: ");
        scanf("%f", &eficienciaMotores); getchar();

        if ( eficienciaMotores < 0.0 || eficienciaMotores > 90.0 ) {

            printf("\n Desculpe, mas a eficiencia do seu motor nao pode ser negativa e nem maior que o de fabrica. Tente novamente: ");
            scanf("%f", &eficienciaMotores); getchar();

            if ( eficienciaMotores < 0.0 || eficienciaMotores > 90.0 ) {

                printf("O valor da eficiencia foi digitado incorretamente pela segunda vez seguida. \n Saindo...");
                getchar();
                return 0;

            }

        }

        /* Realizacao dos calculos */

        /* Calculo da Massa da nave
            Massa = numero de motores * peso de cada motor em gravits + 14000
            15 gravits por motor e dado no roteiro */
        massaNaveTotal = numeroMotores*pesoMotor +  pesoNave;

        /* Rendimento em HiperEspaço = Rendimento Normal / 5 = 5 Wormholes por Combuston / 5 = 1 Wormhole por Combuston */
        rendimentoHiperEspaco = rendimentoNormal/5;

        /* Distancia Maxima =
                                Eficiencia * Numero de Motores * RendimentoHiperEspaco * Combustivel por motor + Massa da Nave * Gravidade

                                Do jeito que o calculo foi feito, está havendo pouca influência dos dados na distância maxima
                                a ser percorrida. Dessa forma, quase sempre é possível fazer a viagem a Oya
                                Talvez seja causado pela formula dizer no segundo fator (m*g) que a distância máxima aumenta em
                                função da gravidade e da massa da nave, o que não faz sentido, já que a forte gravidade dificulta
                                a viagem e prejudica o desempenho. */
        distanciaMaxima = ( 1.0*(eficienciaMotores/100.0)*numeroMotores*rendimentoHiperEspaco*(quantidadeCombustivel/numeroMotores) + (1.0*massaNaveTotal*gravidadeLocal))/1000.0;

        /* DEBUG
        printf("\n\n distancia maxima: %.2f", distanciaMaxima); */

        /* Calculo da distancia a percorrer. Distancia entre dois pontos no espaco */
        distanciaPercorrer = sqrt ( pow((coordenadaAtualEixoX - coordenadaOyaEixoX),2) + pow((coordenadaAtualEixoY - coordenadaOyaEixoY),2) + pow((coordenadaAtualEixoZ - coordenadaOyaEixoZ),2) );

        if (distanciaPercorrer > distanciaMaxima) {

            /* Nao sera possivel realizar a viagem */
            printf("\nDesculpe, mas nao e possivel realizar essa viagem. Escolha outro planeta mais proximo para arrumar a nave antes.\n");
            getchar();
        } else {

            /* E possivel realizar a viagem */
            printf("\n\nE ossivel realizar essa viagem! A distancia calculada a ser percorrida e menor que a distancia maxima com as condicoes atuais.");
            printf("\nDeseja continuar? (S/N): ");
            scanf("%c", &continuarViagem); getchar();

            if ( toupper(continuarViagem) != 'S' && toupper(continuarViagem) != 'N' ) {

                printf("Desculpe , mas essa nao e uma opcao valia. Sao aceitas somente as letras S e N. Tente novamente: ");
                scanf("%c", &continuarViagem); getchar();

                if ( toupper(continuarViagem) != 'S' && toupper(continuarViagem) != 'N' ) {

                    printf("A tecla de confirmação foi digitada incorretamente pela segunda vez seguida. \n Saindo...");
                    getchar();
                    return 0;

                }

            }

            /* Gerar relatorio */
            printf("\n\n\n\n");
            printf("**************************************************\n");
            printf("******** Relatorio de Calculos para Viagem********\n");
            printf("Quantidade atual de combustível - c: %.2f\n", quantidadeCombustivel);
            printf("Quantidade de motores restantes - n: %d\n", numeroMotores);
            printf("Posicao atual: (%.2f,%.2f,%.2f)\n", coordenadaAtualEixoX, coordenadaAtualEixoY, coordenadaAtualEixoZ);
            printf("Gravidade local: %.2f\n", gravidadeLocal);
            printf("Massa total da nave: %.2f\n", massaNaveTotal);

            printf("Posicao de Oya (%.2f,%.2f,%.2f)\n", coordenadaOyaEixoX, coordenadaOyaEixoY, coordenadaOyaEixoZ);
            printf("Distancia estimada entre o local atual e Oya: %.2f\n\n", distanciaPercorrer);
            printf("Distancia maxima que pode ser percorrida pela nave: %.2f\n\n", distanciaMaxima);
            printf("OBS: A distancia estimada foi dada pela formula:\n");
            printf("e*n*rh*comb + m*g, em que:\n");
            printf("e e a eficiência dos motores, n e o numero de motores\n");
            printf("rh e o rendimento em hiperespaco do combustivel, \n");
            printf("comb e a quantidade de combustivel, m e a massa total da nave incluindo motores e\n");
            printf("g e a gravidade local.\n");
            printf("**************** Fim do relatorio ****************\n");
            printf("**************************************************\n");
            printf("******************* PROCON 151 *******************\n");
            printf("**************************************************\n");

        }

    } else if (opcaoSelecionadaMenu == 2) {
        /* Entendi que o arquivo teria que ser criado na funcao principal
        e os caracteres da amostra de DNS passados para a funcao.
        Obviamente, por referencia */
        printf("Entrando na funcao do simulador genetico.\n");

        while (nomeArquivo[0] != '0') {
            printf("Digite o nome do arquivo que sera a amostra analisada\n");
            printf("ou digite 0 (zero) para encerrar.\n");
            scanf("%[^\n]", nomeArquivo); getchar();
            if (nomeArquivo[0] != '0') {
                arquivoAmostra = fopen(nomeArquivo, "rt");            /* Abre arquivo no modo de leitura */
                if (arquivoAmostra == NULL) {
                    /* Em caso de erros na abertura do arquivo, nao continua */
                    printf("Houve um erro ao abrir o arquivo!\n");
                    printf("O SimGene nao pode ser iniciado!\n");
                } else {
                    start_SimGene(arquivoAmostra, fitaDNA1, fitaDNA2, &pilotoAutomatico);
                    fclose(arquivoAmostra);
                }
            } else {
                printf("\nOK, saindo...\n");
            }
        }
        getchar();
        return 0;
    } else if (opcaoSelecionadaMenu == 3) {
        printf("Sinto muito, essa funcao ainda nao e possivel. Volte novamente daqui a alguns dias.\n");
        printf("Me chame novamente quando desejar, estarei disponivel para as demais funcoes.\n");
        return 0;
    } else if (opcaoSelecionadaMenu == 4) {

        /* Nessa opcao, o Wararray deveria fazer qualquer coisa */
        printf("Toc Toc\n");
        getchar();
        printf("Ate mais chefe, boa sorte na missao.\n");
        return 0;

    } else if (opcaoSelecionadaMenu == 5) {

        /* The Great Escape
        Tudo relacionado ao terceiro volume do trabalho sera tratado a partir
        dessa funcao */
        /* printf("\nThe Great Escape\n"); */
        TheGreatEscape (&EM, &D);
    } else {

        /* Replay */
        /* printf("\nReplay\n"); */
        printf("\nFuncao de replay ainda nao implementada!\n\n");
    }

    return 0;

}

void start_SimGene(FILE* arquivoAmostra, char* fitaDNA1, char* fitaDNA2, int* pilotoAutomatico) {

    int i,j;
    char resposta;
    char genes[24][11] = {
        "TCCTGCCATG",
        "TGTATGAAGT",
        "CTCGAAATTA",
        "TTCTACGTAC",
        "TTAGATACGG",
        "TGAAGGGA",
        "AGAGTCATGC",
        "CTGGGTCG",
        "CTACGG",
        "TGACGGCG",
        "GAGGTGGG",
        "TTGAGGCA",
        "TTGGCCGG",
        "CACATA",
        "AGCCCGGC",
        "CTACGG",
        "CTGGAGCTGT",
        "GAGCGG",
        "ACTCAC",
        "GAGTTTATAA",
        "CATATA",
        "TATGACTC",
        "TTGATTCG",
        "TACATA",
    };

    char descricaoGenes[24][100] = {
        "Membrana Externa de Nadadeiras",
        "Composicao da Queratina das garras de Aves",
        "Formador de Polegar Opositor",
        "Estrutura Branquial",
        "Estrutura Pulmonar",
        "Sistema Cardiovascular Fechado",
        "Constituicao Ossea",
        "Pelos",
        "Relacionado a Lactase, presente apeans em mamiferos",
        "SIZE_GENE 1.709E-3 a 93.5",
        "SIZE_GENE 112.6 a 273.7",
        "SIZE_GENE 404 a 666",
        "SIZE_GENE 1303 a 100E3",
        "Exclusivo de Repteis",
        "Sistema Cardiovascular Aberto",
        "Marcador de Mamiferos",
        "Membrana Vitrea",
        "Sistema Nervoso Simples",
        "Reforca Origem Aquatica da vida no Planeta",
        "Presenca de Cartilagens",
        "Sistema Nervoso bem estruturado",
        "Presenca de Penas",
        "Presenca de Escamas",
        "Sistema Nervoso complexo",
    };

    int contadorOcorrenciasGene[24];    /* Numero de ocorrencias de cada gene na amostra */
    int contadorGeralGenes;                /* Conta todos os genes encontrados */

    /* Inicializacao dos contadores como 0 */
    contadorGeralGenes = 0;
    for (i = 0; i < 24; i++) {
        contadorOcorrenciasGene[i] = 0;
    }

    /* nos damos escolha ao usuario, mas e uma pergunta retorica, ele nao
    pode continuar sem ligar o piloto automático */

    if ((*pilotoAutomatico) == 0) {
        printf("**********************************************************************\n");
        printf("**********************************************************************\n");
        printf("******************************          ******************************\n");
        printf("*****************************  WARARRAY  *****************************\n");
        printf("******************************          ******************************\n");
        printf("**********************************************************************\n");
        printf("************************* SIMULADOR GENETICO *************************\n");
        printf("**********************************************************************\n");
        printf("**************** Colocar a nave em piloto automatico? ****************\n");
        printf("*********************** (Digite apenas S ou N) ***********************\n");
        printf("**********************************************************************\n");
        printf("**********************************************************************\n");
        printf("**********************************************************************\n");
        do {
                scanf("%c", &resposta);
        } while (toupper(resposta) != 'S' && toupper(resposta) != 'N');

        if (resposta == 'N') {
            printf("Nao e possivel trabalhar com o simulador genetico com a nave em ");
            printf("modo manual!. Saindo!\n\n");
            return;
        }

    }
    (*pilotoAutomatico) = 1;

    /* Lista de todos os Genes cadastrados */
    printf("====== Lista de todos os genes cadastrados ======\n");
    for (i = 0; i < 24; i++) {
        printf("Gene: %s -- %s\n", genes[i], descricaoGenes[i]);
    }


    /* Le as duas linhas do arquivo */
    fscanf(arquivoAmostra, "%[^\n] %[^\n]", fitaDNA1, fitaDNA2);

    /* Completa as fitas */
    CompletaFitasDNA (fitaDNA1, fitaDNA2);

    /* Conta ocorrencias para calcular a frequencia de cada uma depois */
    for (i = 0; i < 24; i++) {
        contadorOcorrenciasGene[i] += BuscaStringEmString( genes[i], fitaDNA1 );
        contadorOcorrenciasGene[i] += BuscaStringEmString( genes[i], fitaDNA2 );
        contadorGeralGenes += contadorOcorrenciasGene[i];

    }

    /* Calcula e mostra na sequencia o % de ocorrencia de cada gene */
    for (i = 0; i < 24; i++) {
        printf("\nOcorrencia do gene %s: \t\t%d", genes[i], contadorOcorrenciasGene[i]);
        printf("\t(%.2f%%)", ((float)contadorOcorrenciasGene[i]*100.00/contadorGeralGenes) );

        /* Isso aqui e so pra formatar o histograma */
        if ( (float)contadorOcorrenciasGene[i]*100.00/contadorGeralGenes >= 10.00 ) {
            printf("\t|");
        } else {
            printf("\t\t|");
        }

        for (j = 0; j < contadorOcorrenciasGene[i]; j++) {
            printf("|");
        }

    }

    printf("\nTotal de ocorrencias: %d\n", contadorGeralGenes);
    getchar(); getchar();

    printf("\nOs genes mais relevantes (mais de 10 %% de ocorrencia) sao: \n\n");
    for (i = 0; i < 24; i++) {
        if ( (float)contadorOcorrenciasGene[i]*100.00/contadorGeralGenes >= 10.00 ) {
            printf("%s - %s  (%.2f %%)\n", genes[i],
            descricaoGenes[i], (float)contadorOcorrenciasGene[i]*100.00/contadorGeralGenes);
        }
    }
    getchar();

}

void CompletaFitasDNA (char* fitaDNA1, char* fitaDNA2) {

    int i = 0;

    /* Percorrera as duas linhas do DNA e as completa */
    /* DEBUG
    printf("Linha 1:\n%s\n", fitaDNA1);
    printf("Linha 2:\n%s\n", fitaDNA2);
    */

    /* Completa as informacoes que faltam nas fitas de DNA
    ligacoes possiveis sao: A-T e G-C, vide:
    http://brasilescola.uol.com.br/biologia/transcricao.htm
    http://www.infoescola.com/genetica/estrutura-do-dna/
    Vale observar que U so e usado no RNA no momento da copia do DNA
    U sempre se liga com A.
    Aqui, dei preferencia a ligar A com T*/
    while (fitaDNA1[i] != '\0' && fitaDNA2[i] != '\0') {

        if ( fitaDNA1[i] == '*' ) {

            if (fitaDNA2[i] == 'U' || fitaDNA2[i] == 'T') {
                fitaDNA1[i] = 'A';
            } else if (fitaDNA2[i] == 'A') {
                fitaDNA1[i] = 'T';
            } else if (fitaDNA2[i] == 'C') {
                fitaDNA1[i] = 'G';
            } else if (fitaDNA2[i] == 'G') {
                fitaDNA1[i] = 'C';
            }

        } else if ( fitaDNA2[i] == '*' ) {

            if (fitaDNA1[i] == 'U' || fitaDNA1[i] == 'T') {
                fitaDNA2[i] = 'A';
            } else if (fitaDNA1[i] == 'A') {
                fitaDNA2[i] = 'T';
            } else if (fitaDNA1[i] == 'C') {
                fitaDNA2[i] = 'G';
            } else if (fitaDNA1[i] == 'G') {
                fitaDNA2[i] = 'C';
            }
        }
        i++;
    }

    /* DEBUG

    printf("\nFitas apos correcao:\n");
    printf("Linha 1:\n%s\n", fitaDNA1);
    printf("Linha 2:\n%s\n", fitaDNA2);
    */
}

int BuscaStringEmString (char *str1, char *str2) {

  /*um e umdois */
  int i = 0;
  int j = 0;
  int achou = 0;

  do {
    /* Limpa o indice de pesquisa na primeira string */
    i = 0;

    /* percorre a string 2 pelo caractere da string 1 */
    while ( str1[i] != str2[j] && str2[j] != '\0' ) {
      j++;
    }

    /* Quando achado o caractere da string1 na string2, verifica se os que
    sucedem tambem sao iguais ate encontrar o fim de uma das strings */
    while( (str1[i] == str2[j]) && (str1[i] != '\0') && ( str2[i] != '\0') ) {
      i++;
      j++;
    }

    /* Se a primeira string chegou ao fim, foi porque ela foi incrementada
    ate o seu fim no laco anterior, ou seja, todos os caracteres foram
    encontrados, logo sinaliza na flag
    Se a segunda chegou ao fim antes da primeira, a primeira nao foi encontrada
    na segunda.*/

    if ( str1[i] == '\0' ) {
      achou++;
    }

  } while ( str2[j] != '\0' );

  return achou;
}

void TheGreatEscape (nave *EM, nave *D) {
    /* DEBUG:
     printf("\nThe Great Escape is in da house\n"); */

     int tamanhoMaximoMapa = 100;
     char mapa[tamanhoMaximoMapa*(tamanhoMaximoMapa+1)];        /* Isso e uma matriz 2d tratada como vetor */
     int numLinhas = 0;
     int tamanhoMapa = 20;                    /* Roteiro */
     int modo;                                            /* modo de jogo: 0: tenente; 1: Dr. Flame */
     char continua = 'n';

     /* Tudo isso esta dentro de um laco pois o usuario pode querer jogar quantas
     vezes quiser */
        do {

            /* Inicializacao da nave da Tenente
            Aqui, para evitar que no modo de batalha o usuario tenha que fazer todo o calculo
            do hiper-espaco para determinar coisas como combustivel e numero de motores,
            resolvi colocar o maximo de motores pois essa e obviamente uma vantagem competitiva
            uma vez que eles serao destruidos durante as batalhas.

            Notar tambem que as naves sao reinicializadas a cada nova partida*/

            CopiaStrings ("Earthquake Machine", EM->nome, 20);
            EM->contadorRodadas = 0;
            EM->integridadeCasco = 150;
            EM->rodadasRaioDaMorte = 0;
            EM->contadorTempestadeLerigou = 0;
            EM->contadorMeteoroPegasus = 0;
            EM->energia = 600;
            EM->energiaBloqueada = 0;
            EM->contadorProtegoMaxima = 0;
            EM->contadorRepelloInimigotum = 0;
            EM->numMotores = 4;
            EM->combustivel = EM->numMotores*50;
            EM->posX = -1;
            EM->posY = -1;

            /* Inicializacao da nave do Dr. Flame
            Mesmas observacoes da outra nave  */

            CopiaStrings ("Dr. Flame", D->nome, 10);
            D->contadorRodadas = 0;
            D->integridadeCasco = 150;
            D->rodadasRaioDaMorte = 0;
            D->contadorMeteoroPegasus = 0;
            D->contadorRodadas = 0;
            D->contadorTempestadeLerigou = 0;
            D->energia = 600;
            D->energiaBloqueada = 0;
            D->contadorProtegoMaxima = 0;
            D->contadorRepelloInimigotum = 0;
            D->numMotores = 4;
            D->combustivel = D->numMotores*50;

            /* Tam max do mapa
            LeiaMapa faz a leitura passando o tamanhoMapa (20 como pedido no roteiro)
            e o tamanho maximo do mapa (100 conforme explicado no roteiro)
            Como pode vir um mapa com qualquer valor entre os dois, eu peco
            para retornar o numero de linhas lidas do arquivo de texto
            Se numLInhas e zero, ha erro na leitura. O programa insiste ate o arquivo
            conseguir ser lido corretamente */
            while (numLinhas == 0) {
                numLinhas = LeiaMapa(mapa, tamanhoMaximoMapa, tamanhoMapa);
            }

            /* Menu
            Mais a frente o codigo motra que a unica diferena entre os dois modos
            e que a tenente deve navegar pelo mapa fugindo.
            Isso nao ocorre com Dr. Flame
            Para alcancar isso, a funcao de batalha teve de ser feita o mais generica
            possivel */
            printf("**********************************************************************\n");
            printf("**********************************************************************\n");
            printf("**********************************************************************\n");
            printf("************************* THE GREAT ESCAPE ***************************\n");
            printf("**********************************************************************\n");
            printf("*********************** 1 Jogar como a tenente ***********************\n");
            printf("*********************** 2 Jogar como Dr. Flame ***********************\n");
            printf("**********************************************************************\n");
            printf("**********************************************************************\n");
            printf("**********************************************************************\n");

            scanf("%d", &modo); getchar();
            /* Verifica constantemente a entrada do usuario ate que ele acerte */
            while (modo != 1 && modo != 2) {
                printf("\nEscolha invalida. Escolha apenas 1 ou 2: ");
                scanf("%d", &modo); getchar();
            }

            /* DEBUG: Lembrar de criar variavel i para usar
            LimpaTela();
            printf("\nConteudo lido do arquivo: \n");
            for (i = 0; i < numLinhas; i++) {
             printf("mapa[%02d]: %s\n", i, (mapa + tamanhoMaximoMapa*i) );
         } */

            if (modo == 1) {
                /* Jogar como tenente */
                printf("Endereco %p\n", EM);
                IniciarFugaTenente(EM, D, mapa, numLinhas, tamanhoMapa, tamanhoMaximoMapa);
            } else {
                /* Jogar como Dr. Flame
                Note que a funcao Batalhar correspondente ja e chamada diretamente
                Acima, para a tenente a fuga e iniciada, o que faz com que o usuario
                navegue pelo mapa. Com Dr. Flame isso nao ocorre. */
                BatalhaComoFlame(EM, D, mapa, numLinhas, tamanhoMapa, tamanhoMaximoMapa);
            }

            /* Quando as partidas terminam (funcoes retornam),
            a tela e limpada e uma mensagem indica o fim do jogo
            O usuario e questionado se deseja jogar de novo, pois, de acordo com
            o roteiro, o programa nao pode fechar a nao ser que o usuario deseje
            sair */
            LimpaTela();
            printf("Fim de partida. Deseja jogar novamente?(S/N)");
            scanf("%c", &continua); getchar();

            while (toupper(continua) != 'S' && toupper(continua) != 'N') {
                printf("\nOpcao incorreta. Digite novamente: ");
                scanf("%c", &continua); getchar();
            }

        } while (toupper(continua) ==  'S');


}

/* Auto-explicativo*/
void CopiaStrings (char *strOrigem, char *strDestino, int tam) {

    int i;
    for (i = 0; i < tam; i++) {
        strDestino[i] = strOrigem[i];
    }

}

int LeiaMapa (char *mapa, int tam, int tamMapa) {
    /* Retorna numero de linhas lidas */
    int contadorLinhas  = 0;
    int i,teste;
    int flag = 0;
    int flagProblema = 0;
    char continua = 's';
    char nomeArquivo[100] = "mapRun.txt";    /* conforme solicitado no roteiro */
    FILE *fp;

    /* A mensagem lembra o usuario de colocar o mapa na pasta */
    printf("\nIniciaremos a leitura do mapa. Certifique-se de que mapRun.txt esta na pasta de execucao do programa.\n\n");
    getchar();

    fp = fopen(nomeArquivo, "rt");
     while (fp == NULL && (continua == 's' || continua == 'S')) {
        printf("Erro na abertura do arquivo. Deseja tentar novamente (S/N)? Coloque o arquivo mapRun.txt na pasta de execucao do programa\n");
        scanf("%c", &continua); getchar();
        if (continua == 'S' || continua == 's') {
            fp = fopen(nomeArquivo, "rt");
        }
    }

    for (i = 0; i < tam && flag == 0 && flagProblema == 0; i++) {
        teste = fscanf(fp, " %[^\n]", (mapa + tam*i) );
        if ( TamanhoString ((mapa + tam*i)) != tamMapa && TamanhoString((mapa + tam*i)) != 0 ) {
            /* ultima string sempre tem tam. 0
            e as colunas devem estar de acordo com o tamanho configurado na
            funcao principal (20 de acordo com o roteiro)
            Caso as duas condicoes nao estejam satisfeitas, sobe a flag indicando erro*/
            flagProblema = 1;
        }
        if (teste == 1) {
            /* fscanf retorna um a cada "match" que ocorre na condicao de filtragem
            especificada. No caso, devido ao parametro '%[^\n]', a cada linha lida */
            contadorLinhas++;
        } else {
            /* acabou */
            flag = 1;
        }
    }

    /* A mesma verificacao feita para colunas e feita para as linhas */
    if (contadorLinhas != tamMapa) {
        flagProblema = 1;
    }

    if (flagProblema) {
        printf("\nParece que ha um problema com seu arquivo de mapa, verifique e pressione algo para tentar novamente.\n");
        contadorLinhas = 0;    /* faz retornar zero em caso de problemas */
        flagProblema = 0;
        flag = 0;
    }
    fclose(fp);
    return contadorLinhas;
}

void LimpaTela () {
    /* Exige stdlib.h e faz o codigo nao ser portavel pra Windows.
    para Windows, trocar para system("cls") */
    system("clear");
}

/* Auto-explicativo */
int TamanhoString (char* str) {

    int i = 0;

    while (str[i] != '\0') {
        i++;
    }

    /* DEBUG:
    printf("Tamanho string: %d", i); */
    return i;

}

/* percorre a matriz bi-dimensional exibindo os caracteres na tela
Assim ela mostra o mapa
utilizei passagem por referencia usando ponteiros e indexei a matriz
2D como se fosse um vetor simples, considerando as linhas colocadas
uma apos a outra sequencialmente */
void ExibeMapa (char *mapa, int linhas, int tam) {

    int i,j;
    char c;
    for (i = 0; i < linhas; i++) {
        for (j = 0; j < tam; j++) {
            c = (*(mapa + tam*i + j));    /* so pra ficar mais bonito dentro do if */
             if ( c == 'D' || c == '0' ) {
                 /* Se for a nave inimiga ou buraco negro, esconde, conforme roteiro */
                printf(" ");
            } else {
                /* caso contrario, mostra normalmente */
                printf("%c", c);
            }
        }
        printf("\n");
    }
}

/* Posiciona a nave aleatoriamente no mapa.
Chamada so uma vez.
Sim, rand() nao e totalmente aleatorio, isso deve ser modificado
para utilizar uma seed baseada na timestamp atual */
void PosicionaNave (char *mapa, int linhas, int tam, char indicador, nave *EM) {

    /* DEBUG:
    printf("Endereco EM: %p", EM);
    getchar(); */


    while ( (*(mapa + EM->posX*tam + EM->posY)) != ' ' ) {
        /* Gera posicao aleatoria ate que a nave seja colocada em um lugar
        em que nao ha nada */

        EM->posX = rand() % 20;
        EM->posY = rand() % 20;
    }

    /* primeira letra da nave */
    (*(mapa + (EM->posX)*tam + EM->posY)) = indicador;

}

void IniciarFugaTenente (nave *EM, nave *D, char* mapa, int numLinhas, int tamanhoMapa, int tamanhoMaximoMapa) {

    int estadoMovimento;
    char movimento;
    int para = 0;
    char mensagemUsuario[100] = "Nenhuma mensagem nova.";    /* Essa mensagem e sempre exibida ao final dos stats*/
    int resultado;
    LimpaTela();
    ExibeMapa (mapa, numLinhas, tamanhoMaximoMapa);

    printf("\n\n Pressione algo para posicionar nave...\n\n");
    getchar();

    /* essas funcoes sao as que fazem tudo. Basta chama-las */
    PosicionaNave (mapa, numLinhas, tamanhoMaximoMapa, 'E', EM);
    LimpaTela();
    ExibeMapa (mapa, numLinhas, tamanhoMaximoMapa);
    ExibeStatus (EM, D, mensagemUsuario);

    /* Para a mensgagem aparecer ao usuario, ela e copiada para mensagemUsuario
    pois essa string e sempre mostrada pela funcao ExibeStatus.
    Isso evita o printf baguncar as coisas */
    while (para == 0) {
        scanf("%c", &movimento); getchar();
        estadoMovimento = MovimentaNave (EM, mapa, movimento, tamanhoMaximoMapa);
        if (estadoMovimento == 0) {
            /* 0 esta tudo OK, mas usuario mandou em direcao a um obstaculo */
            CopiaStrings("Voce nao pode jogar a nave sobre um asteroide!!!\nProximo movimento: ", mensagemUsuario, 100);
        } else if (estadoMovimento == 2) {
            CopiaStrings("Encontrou buraco negro!!!", mensagemUsuario,100);
        } else if (estadoMovimento == -10) {
            /* -10 e retornado quando acaba combustivel e/ou motores
            Encerra a jogada */
            LimpaTela();
            printf("Infelizmente seu combustivel acabou :(");
            printf("\nParece que e fim de jogo para nos...");
            printf("\nPressione qualquer tecla para sair.");
            getchar();
            return;
        } else if (estadoMovimento != 1) {
            /* Se for qualquer um dos outros valores que não indicam OK (2 ou 3), sai do laco
            para iniciar a batalha */

            para = 1;
        }
        LimpaTela();
        ExibeMapa (mapa, numLinhas, tamanhoMaximoMapa);
        ExibeStatus (EM, D, mensagemUsuario);
        /* Essa string e deixara pronta para a proxima atualizacao de tela */
        CopiaStrings("Proximo movimento: ", mensagemUsuario, 100);
    }
    para = 0;

    LimpaTela();
    ExibeMapa (mapa, numLinhas, tamanhoMaximoMapa);
    if (estadoMovimento == 3){
        /* Dr. Flame */
        LimpaTela();
        CopiaStrings("Encontrou Dr. Flame!!!", mensagemUsuario,100);
        ExibeStatus (EM, D, mensagemUsuario);
        getchar();

        /* A partir daqui, modo de batalha */
        /* note o nome IniciarBatalha */
        resultado = IniciarBatalha(EM, D, mensagemUsuario, mapa, numLinhas, tamanhoMaximoMapa);

        LimpaTela();
        if (resultado == 1) {
            /* ele deveria voltar para o mapa e permitir a navegacao da comandante
            mas... nao deu
            Exibe mensagem pro usuario ficar feliz */
            printf("\nVoce venceu!!!\n");
            getchar();
        } else {
            printf("\nVoce perdeu!!!\n");
            getchar();
        }

    } else if (estadoMovimento == 4) {
        /* Fenda */
        LimpaTela();
        CopiaStrings("Chegou a fenda!!!", mensagemUsuario,100);
        ExibeStatus (EM, D, mensagemUsuario);
    } else if (estadoMovimento == -10) {
        return;
    }
}

void BatalhaComoFlame (nave *EM, nave *D, char* mapa, int numLinhas, int tamanhoMapa, int tamanhoMaximoMapa) {

    int resultado;
    char mensagemUsuario[100] = "Nenhuma mensagem nova.";

    LimpaTela();

    /* A partir daqui, modo de batalha */
    /* note que a funcao e a mesma usada para a comandante
    Porem, a ordem das naves e invertida */
    resultado = IniciarBatalha(D, EM, mensagemUsuario, mapa, numLinhas, tamanhoMaximoMapa);
    getchar();
    LimpaTela();
    if (resultado == 1) {
        printf("\nVoce venceu!!!\n");
        getchar();
    } else {
        printf("\nVoce perdeu!!!\n");
        getchar();
    }

}

int MovimentaNave (nave *EM, char* mapa, char movimento, int tam) {
    /* Essa funcao movimenta a nave e atualiza as informacoes da nave de
    acordo com o movimento
    Observacao: X e vertial e nao horizontal como esperado */

    int posXNova;
    int posYNova;
    char cPos = ' ';
    int flag;

    if (toupper(movimento) == 'D') {
        posXNova = EM->posX;
        posYNova = EM->posY + 1;
    } else if (toupper(movimento) == 'S') {
        posXNova = EM->posX + 1;
        posYNova = EM->posY;
    } else if (toupper(movimento) == 'A') {
        posXNova = EM->posX;
        posYNova = EM->posY - 1;
    } else if (toupper(movimento) == 'W') {
        posXNova = EM->posX - 1;
        posYNova = EM->posY;
    } else {

        return 1;
    }

    cPos = (*(mapa + (posXNova)*tam + (posYNova)));

    if ( cPos == '*' ) {
        return 0;
    } else if ( cPos == '/' ) {
        flag = 4;
    } else if ( cPos == '0' ){
        /* Buraco Negro
        Roteiro: perde 2 motores e danifica casco em 20 koikes
        Quantidade de combustivel que havia distribuida nos motores e subtraida*/
        EM->integridadeCasco-=20;
        EM->combustivel-= (EM->combustivel*2/(EM->numMotores));
        EM->numMotores-=2;
        flag = 2;
    } else if ( cPos == 'D') {
        /* Encontrou Dr. Flame */
        flag = 3;
    } else {
        /* Movimento normal, remove 1 combuston de acordo com roteiro */
        EM->combustivel-=1;
        flag = 1;
    }

    /* Checar combustivel na hora do movimento da nave */
    if (EM->combustivel > 0) {
        /* Deixa caractere antigo em branco
            O que elimina os buracos negros do mapa. Ainda bem que isso e ficcao
            E coloca a nave na nova posicao
        */
        (*(mapa + (posXNova)*tam + (posYNova))) = (*(mapa + EM->posX*tam + EM->posY));
        (*(mapa + EM->posX*tam + EM->posY)) = ' ';
        EM->posX = posXNova;
        EM->posY = posYNova;
    }
    else {
        return -10;
    }

    return flag;

}

void ExibeStatus (nave *EM, nave *D, char *extra) {

    int i = 0;

    /* tudo isso aqui e puramente cosmetico */
    printf("\n");
    printf("Rodadas: %d\n", EM->contadorRodadas);
    /* observe o uso de "sua nave" e "nave inimiga" mais abaixo
    isso permite que a mesma coisa seja usada para os modos de jogo como
    Dr. Flame e como tenente

    Abaixo, os lacos imprimem | de forma a fazer uma "barra de HP"
    Como em : Casco ||||||||        (x/100) por exemplo
    Isso se repete para varios contadores e tudo se repete para a nave
    inimiga  */
    printf("--- STATUS SUA NAVE ---\n");
    printf("Casco:       ");
    for (i = 0; i < ( (int) 100*(EM->integridadeCasco/(float)300) ); i++) {
        printf("|");
    }
    for (i = (int) 100*(EM->integridadeCasco/(float)300); i < 50; i++ ) {
        printf(" ");
    }
    printf(" %d/150\n", EM->integridadeCasco);

    printf("Energia:     ");
    if (EM->energiaBloqueada > 0) {
        for (i = 0; i < 50; i++ ) {
            printf(" ");
        }
    } else {
        for (i = 0; i < ( (int) 100*(EM->energia/(float)1200) ); i++) {
            printf("|");
        }
        for (i = (int) 100*(EM->energia/(float)1200); i < 50; i++ ) {
            printf(" ");
        }
    }
    for (i = (int) 100*(EM->energia/(float)1200); i < 50; i++ ) {
        printf(" ");
    }
    printf(" %d/600\n", EM->energia);

    printf("Combustivel: ");
    for (i = 0; i < ( (int) 100*(EM->combustivel/(float)400) ); i++) {
        printf("|");
    }
    for (i = (int) 100*(EM->combustivel/(float)400); i < 50; i++ ) {
        printf(" ");
    }
    printf(" %d/200\n", EM->combustivel);

    printf("Num. Motores: %d/4\n", EM->numMotores);
    printf("Rodadas para proximo raio da morte: %d\n", EM->rodadasRaioDaMorte);
    printf("Meteoro de Pegasus usados: %d, ", EM->contadorMeteoroPegasus);
    printf("Tempestade Lerigou usadas: %d, ", EM->contadorTempestadeLerigou);
    printf("Rodada do Protego Maxima: %d\n", EM->contadorProtegoMaxima);
    printf("Rodada do Repello Inimigotum: %d\n", EM->contadorRepelloInimigotum);

    printf("-----------------------------\n");
    printf("--- STATUS NAVE INIMIGA ---\n");
    printf("Casco:       ");
    for (i = 0; i < ( (int) 100*(D->integridadeCasco/(float)300) ); i++) {
        printf("|");
    }
    for (i = (int) 100*(D->integridadeCasco/(float)300); i < 50; i++ ) {
        printf(" ");
    }
    printf(" %d/150\n", D->integridadeCasco);

    printf("Energia:     ");
    if (D->energiaBloqueada > 0) {
        for (i = 0; i < 50; i++ ) {
            printf(" ");
        }
    } else {
        for (i = 0; i < ( (int) 100*(D->energia/(float)1200) ); i++) {
            printf("|");
        }
        for (i = (int) 100*(D->energia/(float)1200); i < 50; i++ ) {
            printf(" ");
        }
    }

    printf(" %d/600\n", D->energia);

    printf("Combustivel: ");
    for (i = 0; i < ( (int) 100*(D->combustivel/(float)400) ); i++) {
        printf("|");
    }
    for (i = (int) 100*(D->combustivel/(float)400); i < 50; i++ ) {
        printf(" ");
    }
    printf(" %d/200\n", D->combustivel);

    printf("Num. Motores: %d/4\n", D->numMotores);
    printf("Rodadas para proximo raio da morte: %d\n", D->rodadasRaioDaMorte);
    printf("Tempestade Lerigou usadas: %d, ", D->contadorTempestadeLerigou);
    printf("Meteoro de Pegasus usados: %d, ", D->contadorMeteoroPegasus);
    printf("Rodada do Protego Maxima: %d\n", D->contadorProtegoMaxima);
    printf("Rodada do Repello Inimigotum: %d\n", D->contadorRepelloInimigotum);

    /* mensagem adicional ao usuario */
    printf("\n%s\n", extra);

}

int IniciarBatalha (nave *MinhaNave, nave *NaveInimiga, char *mensagemUsuario, char *mapa, int numLinhas, int tamanhoMaximoMapa) {

    /*
    Aqui esta implementada a logica de batalha conforme interpretado a partir
    do roteiro.

    Todas as variaveis passadas aqui para essa funcao sao necessarias
    para chamar as demais funcoes
    Retorna 1 se ganhou ou 0 se perdeu */

    int escolha, dano;
    int escolhaInimigo;
    int flagTempestadeLerigouInimigo;
    char parImparInimigo;

    do {

        /* o legal de usar nomes tao obvios como variaveis
        e que eu quase nao preciso explicar nos comentarios o que esta ocorrendo */

        flagTempestadeLerigouInimigo = 0;
        /* Contadores de rodadas */
        MinhaNave->contadorRodadas += 1;
        NaveInimiga->contadorRodadas += 1;
        /* Decrementa rodadas para usar o raio da morte */
        if (MinhaNave->rodadasRaioDaMorte > 0) {
            MinhaNave->rodadasRaioDaMorte -= 1;
        }
        if (NaveInimiga->rodadasRaioDaMorte > 0) {
            NaveInimiga->rodadasRaioDaMorte -= 1;
        }

        /* Energia bloqueada por X rodadas.
        Decrementa contadores a cada rodada */
        if (MinhaNave->energiaBloqueada > 0) {
            MinhaNave->energiaBloqueada--;
        }
        if (NaveInimiga->energiaBloqueada > 0) {
            NaveInimiga->energiaBloqueada--;
        }
        /* Incrementa as rodadas em que o escudo permaneceu em uso */
        if (MinhaNave->contadorProtegoMaxima > 0) {
            if (MinhaNave->contadorProtegoMaxima == 5) {
                MinhaNave->contadorProtegoMaxima = 0;
            }
            /* monitora a energia utilizada. 50 DF por rodada
            Se não tiver energia na rodada, esquece, o escudo e desativado para
            as subsequentes */
            if (MinhaNave->energia < 50) {
                /* Acabou a energia a ser usada pelo escudo */
                MinhaNave->contadorProtegoMaxima = 0;
            } else {
                /* Tem energia, subtrai e conta */
                MinhaNave->energia -= 50;
                MinhaNave->contadorProtegoMaxima += 1;
            }
        }
        if (NaveInimiga->contadorProtegoMaxima > 0) {
            if (NaveInimiga->contadorProtegoMaxima == 5) {
                NaveInimiga->contadorProtegoMaxima = 0;
            }
            if (NaveInimiga->energia < 50) {
                /* Acabou a energia a ser usada pelo escudo */
                NaveInimiga->contadorProtegoMaxima = 0;
            } else {
                NaveInimiga->energia -= 50;
                NaveInimiga->contadorProtegoMaxima += 1;
            }
        }

        LimpaTela();
        ExibeStatus (MinhaNave,NaveInimiga,mensagemUsuario);
        CopiaStrings("Batalha em andamento", mensagemUsuario,100);
        escolha = EscolhaArmamento ();

        /* nao faremos muitas verificacoes na escolha do inimigo pois isso
        tera que ser feito no programa dele
        Ele so vai nos passar a escolha dele apos verificacao da mesma com sucesso
        em seu proprio programa */
        printf("\nDigite a escolha do inimigo: ");
        scanf("%d", &escolhaInimigo); getchar();

        while (escolhaInimigo > 5 || escolhaInimigo < 1) {
            printf("\nEscolha invalida. Tente novamente: ");
            scanf("%d", &escolhaInimigo); getchar();
        }

        /* Procedimentos com escolha do inimigo */
        if (escolhaInimigo == 1) {
            NaveInimiga->rodadasRaioDaMorte = 3;
            NaveInimiga->energiaBloqueada = 2;

            if (MinhaNave->contadorProtegoMaxima > 0) {
                /* O escudo influencia no dano recebido */
                dano = 80 - MinhaNave->contadorProtegoMaxima*5;
            } else {
                dano = 80;
            }

            /* essa logica se repete com frequencia no codigo
            Se a quantidade e menor que o dano, zera para evitar numeros
            negativos */
            if (MinhaNave->integridadeCasco < dano) {
                MinhaNave->integridadeCasco = 0;
            } else {
                MinhaNave->integridadeCasco -= dano;
            }
            MinhaNave->numMotores -= 1;
        }

        if (escolhaInimigo == 2) {
            NaveInimiga->contadorMeteoroPegasus += 1;

            /* sempre implementada logica do roteiro
            Entendi que o dano de meteoro de pegasus é 10*Qtd_utilizada
            Então, na decima utilizacao dos meteoros, ele traria 100 de dano */
            if (MinhaNave->integridadeCasco < 10*NaveInimiga->contadorMeteoroPegasus) {
                MinhaNave->integridadeCasco = 0;
            } else {
                MinhaNave->integridadeCasco -= 10*NaveInimiga->contadorMeteoroPegasus;
            }
        }

        if (escolhaInimigo == 3) {
            /* Inutiliza o escudo ativo */
            flagTempestadeLerigouInimigo = 1;

            if (MinhaNave->contadorProtegoMaxima > 0) {
                MinhaNave->contadorProtegoMaxima = 0;
            } else if (MinhaNave->contadorRepelloInimigotum > 0) {
                MinhaNave->contadorRepelloInimigotum = 0;
            }
            NaveInimiga->contadorTempestadeLerigou += 1;
        }

        if (escolhaInimigo == 4) {
            /* Subtrai Energia */
            NaveInimiga->energia -= 200;
            NaveInimiga->contadorProtegoMaxima += 1;
        }

        if (escolhaInimigo == 5) {
            /* Subtrai energia */
            NaveInimiga->energia -= 200;
            NaveInimiga->contadorRepelloInimigotum -= 1;

            printf("Resultado Inimigo P ou I?");
            scanf("%c", &parImparInimigo); getchar();

            while (toupper(parImparInimigo) != 'P' && toupper(parImparInimigo) != 'I') {
                printf("\nInvalido. Tente novamente: ");
                scanf("%c", &parImparInimigo); getchar();
            }

            if (parImparInimigo == 'P') {
                /* par */
                /* Rouba energia e integridade */
                if (MinhaNave->integridadeCasco < 10) {
                    NaveInimiga->integridadeCasco += MinhaNave->integridadeCasco;
                    MinhaNave->integridadeCasco = 0;
                } else {
                    NaveInimiga->integridadeCasco += 10;
                    MinhaNave->integridadeCasco -= 10;
                }
                if (MinhaNave->energia < 50) {
                    NaveInimiga->energia += MinhaNave->energia;
                    MinhaNave->energia = 0;
                } else {
                    NaveInimiga->energia += 50;
                    MinhaNave->energia -= 50;
                }
            } else {
                /* ímpar */
                NaveInimiga->energia -= 50;
                if (NaveInimiga->integridadeCasco < 5) {
                    NaveInimiga->integridadeCasco = 0;
                } else {
                    NaveInimiga->integridadeCasco -= 5;
                }
            }

        }

        /* Procedimentos com escolha da tenente
        Notar o cuidado bem maior com as verificacoes em relacao as escolhas
        do inimigo */
        while (escolha == 1 && (MinhaNave->rodadasRaioDaMorte > 0 || MinhaNave->energiaBloqueada > 0 || MinhaNave->energia <= 0)) {
            LimpaTela();
            ExibeStatus (MinhaNave,NaveInimiga,mensagemUsuario);
            printf("--- Erro! Voce nao pode usar essa arma");
            getchar();
            escolha = EscolhaArmamento();
        }

        if (escolha == 1 && MinhaNave->rodadasRaioDaMorte == 0) {
            MinhaNave->rodadasRaioDaMorte = 3;
            MinhaNave->energiaBloqueada = 2;

            if (NaveInimiga->contadorProtegoMaxima > 0) {
                /* Se inimigio possui escudo ativado */
                dano = 80 - NaveInimiga->contadorProtegoMaxima*5;
            } else {
                dano = 80;
            }

            if (NaveInimiga->integridadeCasco < dano) {
                NaveInimiga->integridadeCasco = 0;
            } else {
                NaveInimiga->integridadeCasco -= dano;
            }
            NaveInimiga->numMotores -= 1;
            CopiaStrings("Raio da Morte utilizado!", mensagemUsuario, 100);
        }

        if (escolha == 2) {
            MinhaNave->contadorMeteoroPegasus += 1;

            dano = 10*MinhaNave->contadorMeteoroPegasus - NaveInimiga->contadorProtegoMaxima*5;
            if (dano < 0) {
                dano = 0;
            }

            if (NaveInimiga->integridadeCasco < dano) {
                NaveInimiga->integridadeCasco = 0;
            } else {
                NaveInimiga->integridadeCasco -= dano;
            }
            CopiaStrings("Meteoro de Pegasus utilizado!", mensagemUsuario, 100);
        }

        if (escolha == 3) {
            /* Inutiliza o escudo ativo */
            if (NaveInimiga->contadorProtegoMaxima > 0) {
                NaveInimiga->contadorProtegoMaxima = 0;
            } else if (NaveInimiga->contadorRepelloInimigotum > 0) {
                NaveInimiga->contadorRepelloInimigotum = 0;
            }
            MinhaNave->contadorTempestadeLerigou += 1;
            CopiaStrings("Tempestade Lerigou utilizado!", mensagemUsuario, 100);
        }

        if (escolha == 4) {
            /* Subtrai energia */
            if (MinhaNave->energia < 200) {
                CopiaStrings("--- Erro! Voce nao tem energia suficiente.", mensagemUsuario, 100);
            } else {
                if (flagTempestadeLerigouInimigo > 0) {
                    /* lembrando que a tempestade lerigou pode inutilizar esse escudo */
                    CopiaStrings("--- Inutilizado pelo inimigo.", mensagemUsuario, 100);
                    flagTempestadeLerigouInimigo = 0;
                } else {
                    MinhaNave->energia -= 200;
                    MinhaNave->contadorProtegoMaxima += 1;
                    CopiaStrings("Protego Maxima utilizado!", mensagemUsuario, 100);
                }
            }
        }

        if (escolha == 5) {
            /* SUbtrai energia */
            if (MinhaNave->energia < 400) {
                CopiaStrings("--- Erro! Voce nao tem energia suficiente.", mensagemUsuario, 100);
            } else {

                if (flagTempestadeLerigouInimigo > 0) {
                    CopiaStrings("--- Inutilizado pelo inimigo.", mensagemUsuario, 100);
                    flagTempestadeLerigouInimigo = 0;
                } else {

                    MinhaNave->energia -= 200;
                    MinhaNave->contadorRepelloInimigotum += 1;

                    /* Gera numero aleatorio de 0 a 100 */
                    if ( ((rand() % 100)+1)%2 == 0 ) {
                        /* par */
                        /* Rouba energia e integridade*/
                        if (NaveInimiga->integridadeCasco < 10) {
                            MinhaNave->integridadeCasco += NaveInimiga->integridadeCasco;
                            NaveInimiga->integridadeCasco = 0;
                        } else {
                            MinhaNave->integridadeCasco += 10;
                            NaveInimiga->integridadeCasco -= 10;
                        }
                        if (NaveInimiga->energia < 50) {
                            MinhaNave->energia += NaveInimiga->energia;
                            NaveInimiga->energia = 0;
                        } else {
                            MinhaNave->energia += 50;
                            NaveInimiga->energia -= 50;
                        }
                    } else {
                        /* ímpar */
                        MinhaNave->energia -= 50;
                        if (MinhaNave->integridadeCasco < 5) {
                            MinhaNave->integridadeCasco = 0;
                        } else {
                            MinhaNave->integridadeCasco -= 5;
                        }
                    }
                }
            }
        }
    } while (MinhaNave->numMotores > 0 && NaveInimiga->numMotores > 0 && MinhaNave->integridadeCasco > 0 && NaveInimiga->integridadeCasco > 0);

    if (MinhaNave->numMotores <= 0 || MinhaNave->integridadeCasco <= 0 ) {
        /* Eu perdi */
        LimpaTela();
        ExibeStatus (MinhaNave,NaveInimiga,mensagemUsuario);
        return 0;
    } else {
        /* Eu ganhei */
        LimpaTela();
        ExibeStatus (MinhaNave,NaveInimiga,mensagemUsuario);
        return 1;
    }
}

int EscolhaArmamento () {

     int escolha;

     printf("\n");
     printf(" --- LISTA DE MOVIMENTOS POSSIVEIS ---\n");
     printf(" -------- (escolha uma opcao) --------\n");
     printf("1. Arma Raio da Morte\n");
     printf("2. Arma Meteoro de Pegasus\n");
     printf("3. Arma Tempestade Lerigou\n");
     printf("4. Escudo Protego Maxima\n");
     printf("5. Escudo Repello Inimigotum\n");
     printf("Sua escolha: ");
     scanf("%d", &escolha); getchar();

     while (escolha > 5 || escolha < 1) {
         printf("\nEscolha invalida. Tente Novamente: ");
         scanf("%d", &escolha); getchar();
     }

     return escolha;

 }
