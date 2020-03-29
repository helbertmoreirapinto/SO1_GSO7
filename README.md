SO1_GSO7
Trabalhos da disciplina de Sistemas Operacionais 1

<h1>TRABALHO I</h1>
<a href = "https://www.google.com">Link video trabalho 1</a>

<h2>Parte 1</h2>	
<h3>Syscalls de Processo</h3>
<p>A aplicação desenvolvida inicialmente divide o processo em uma bifurcação, de modo que chamaremos de processo core (ou processo pai) o processo cujo ID é inalterado e processo ramo (ou processo filho) o processo cujo retorno da chamada de sistema FORK tenha valor zero.
Exibimos seus respectivos ID's e após cada um aguardar (SLEEP) por um tempo diferente, iniciam programas (SISTEM) já compilados distintos. A chamada de sistema WAIT é utilizada para sincronizar as threads.</p>
<h4>FORK()</h4>Inicia a bifurcação do processo.
<h4>SLEEP()</h4>Faz a thread de execução 'dormir' por um tempo determinado.
<h4>SYSTEM()</h4>Realiza durante a aplicação um comando do terminal do sistema.
<h4>WAIT()</h4>Aguarda a execução das outras threads.

<h3>Syscalls de Memoria</h3>
<p>A ideia da aplicação é mostrar as diferenças entre a utilização de memória compartilhada e memória não compartilhada.
Para simular o multiprocesso e para realizar os testes, utilizamos uma bifurcação no processo, de modo que uma parte do processo (ao qual chamaremos de processo 1) apenas escreve em ambas as memórias (compartilhada e não compartilhada) e a outra parte da bifurcação do processo (ao qual chamaremos de processo 2) apenas lê e exibe os conteúdos das memórias. Podemos notar então a diferença pois as modificações causadas pelo processo 1 na memória não compartlihada não podem ser vistas no processo 2, diferente do que acontece com a memória compartilhada.</p>
<h4>BRK()</h4>Aloca memória para o processo. Similar ao comando calloc em C.
<h4>FTOK()</h4>Retorna uma chave única, para a seleção do local onde será criada a memória. (segurança)
<h4>SHMGET()</h4>Retorna um identificador (também conhecido por descritor) para o início da memória compartilhada.
<h4>SHMAT()</h4>Torna o segmento de memória utilizável. (Anexa a memória ao processo)

<h3>Syscalls de E/S</h3>
<p>A aplicação tenta abrir um arquivo inicialmente inexiste no disco (caso exista a aplicação vai sobreescrever seu conteudo), cria o arquivo e escre uma mensagem nele. Fecha o arquivo. Apos isso abre o arquivo novamente, recupera a informação guardada no arquivo e exibe em tela.</p>
<h4>OPEN()</h4>Realiza a abertura de um arquivo em disco.
<h4>CREAT()</h4>Cria um arquivo no disco.
<h4>WRITE()</h4>Escreve um numero pré definido de bytes no arquivo (ou saida padrão).
<h4>READ()</h4>Lê um numero pre-definido de bytes do arquivo (ou entrada padrão).

<h2>Parte 2</h2>
<h3>CPU-bound</h3>
<p>Para esta parte, desenvolvemos uma aplicação que verifica todos os numeros se são primos ou não no intervalo de 5000 a 30000. Apesar do intervalo ser fixo, quanto mais aumentamos os valores, notamos um estresse maior da CPU.</p>

<h3>I/O-bound</h3>
<p>Para o IO-bound desenvolvemos uma aplicação que le, caracter por caracter, o arquivo de entrada arquivo e o escreve na saida padrao. Como no exemplo anterior, quanto maior o tamanho do arquivo (em quantidade de caracteres), notamos um estresse maior do I/O.</p>
<br/>

<h1>TRABALHO II</h1>
<a href = "https://www.google.com">Link video trabalho 2</a>
<br/>

<h1>TRABALHO III</h1>
<a href = "https://www.google.com">Link video trabalho 3</a>
<br/>

<h1>TRABALHO IV</h1>
<a href = "https://www.google.com">Link video trabalho 4</a>
<br/>
