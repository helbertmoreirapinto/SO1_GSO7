SO1_GSO7
Trabalhos da disciplina de Sistemas Operacionais 1

<h1>TRABALHO I</h1>
<a href = "https://www.google.com">Link video</a>

<h2>Parte 1</h2>	
<h3>Syscalls de Processo</h3>
<p>A aplicação desenvolvida inicialmente divide o processo numa bifurcação, de modo que chamaremos de processo core (ou processo pai) o processo cujo ID é inalterado e processo ramo (ou processo filho) o processo cujo retorno da chamada se sistema FORK tenha valor zero.
Exibimos seus respectivos ID's e apos cada um aguardar(SLEEP) por um tempo diferente, iniciam programas(SISTEM) já compilados distintos. A chamada de sistema WAIT é utilizada para sincronizar as threads.</p>
<h4>FORK()</h4> - Inicia a bifurcação do processo.
<h4>SLEEP()</h4> - Faz a thread de execução 'dormir' por um tempo determinado.
<h4>SYSTEM()</h4> - Realiza durante a aplicação um comando do terminal do sistema.
<h4>WAIT()</h4> - Aguarda a execução das outras threads.

<h3>Syscalls de Memoria</h3>
<p>A ideia da aplicação é mostrar as diferenças entre a utilização de memoria compartilhas e memoria nao compartilhada.
Para simular o multiprocesso e para realizar os testes, utilizamos uma bifurcação no processo, de modo que uma parte do processo (ao qual chamaremos de processo 1) apenas escreve em ambas memorias (compartilhada e nao-compartilhada) e a outra parte da bifurcação do processo (ao qual chamaremos de processo 2) apenas lê e exibe os conteudos das memorias. Podemos notar então a diferença pois as modificações causadas pelo processo 1 na memoria nao-compartlhada nao pode ser vista no processo 2, diferente do que acontece com a memoria compartilhada.</p>
<h4>BRK()</h4> - Aloca memoria para o processo. Similar ao comando calloc em C.
<h4>FTOK()</h4> - Retorna uma chave unica, para a seleção do local onde sera criada a memoria. (segurança)
<h4>SHMGET()</h4> - Retorna um identificador(tambem conhecido por descritor) para o inicio da memoria compartilhada.
<h4>SHMAT()</h4> - Torna o segmento de memoria utilizavel. (Anexa a memoria ao processo)

<h3>Syscalls de E/S</h3>
<p>A aplicação tenta abrir um arquivo inicialmente inexiste no disco (caso exista a aplicação vai sobreescrever seu conteudo), cria o arquivo e escre uma mensagem nele. Fecha o arquivo. Apos isso abre o arquivo novamente, recupera a informação guardada no arquivo e exibe em tela.</p>
<h4>OPEN()</h4> - Realiza a abertura de um arquivo em disco.
<h4>CREAT()</h4> - Cria um arquivo no disco.
<h4>WRITE()</h4> - Escreve um numero pré definido de bytes no arquivo (ou saida padrão).
<h4>READ()</h4> - Lê um numero pre-definido de bytes do arquivo (ou entrada padrão).


<h2>Parte 2</h2>
<h3>CPU_bound</h3>
<p>Para a realização desta parte, desenvolvemos uma
aplicação que dado dois valores positivos (N1 e
N2) encontra todos os numeros primos no intervalo.
Quando utilizamos valores pequenos (relativamente
proximos a zero), o programa não consegue estressar
a CPU. Porem ao utilizar valores grandes, o
processamento aumenta muito, de modo que o SO
reconhece a aplicação como sendo um CPU_bound.</p>

<h3>IO_bound</h3>


<h1>TRABALHO II</h1>
Link video:

<h1>TRABALHO III</h1>
Link video:

<h1>TRABALHO IV</h1>
Link video:

