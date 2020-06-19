SO1_GSO7
Trabalhos da disciplina de Sistemas Operacionais 1

<h1>TRABALHO I</h1>
<a href = "https://youtu.be/nbiwV9bjUtU">Link video trabalho 1</a>

<h2>Parte 1</h2>	
<h3>Syscalls de Processo</h3>
<p>
	A aplicação desenvolvida inicialmente divide o processo em uma bifurcação, de modo que chamaremos de processo core (ou processo pai) o processo cujo ID é inalterado e processo ramo (ou processo filho) o processo cujo retorno da chamada de sistema FORK tenha valor zero.
	Exibimos seus respectivos ID's e após cada um aguardar (SLEEP) por um tempo diferente, iniciam programas (SISTEM) já compilados distintos. A chamada de sistema WAIT é utilizada para sincronizar as threads
</p>
<h4>FORK()</h4>Inicia a bifurcação do processo.
<h4>SLEEP()</h4>Faz a thread de execução 'dormir' por um tempo determinado.
<h4>SYSTEM()</h4>Realiza durante a aplicação um comando do terminal do sistema.
<h4>WAIT()</h4>Aguarda a execução das outras threads.

<h3>Syscalls de Memoria</h3>
<p>
	A ideia da aplicação é mostrar as diferenças entre a utilização de memória compartilhada e memória não compartilhada.
	Para simular o multiprocesso e para realizar os testes, utilizamos uma bifurcação no processo, de modo que uma parte do processo (ao qual chamaremos de processo 1) apenas escreve em ambas as memórias (compartilhada e não compartilhada) e a outra parte da bifurcação do processo (ao qual chamaremos de processo 2) apenas lê e exibe os conteúdos das memórias. Podemos notar então a diferença pois as modificações causadas pelo processo 1 na memória não compartilhada não podem ser vistas no processo 2, diferente do que acontece com a memória compartilhada.
</p>
<h4>BRK()</h4>Aloca memória para o processo. Similar ao comando calloc em C.
<h4>FTOK()</h4>Retorna uma chave única, para a seleção do local onde será criada a memória. (segurança)
<h4>SHMGET()</h4>Retorna um identificador (também conhecido por descritor) para o início da memória compartilhada.
<h4>SHMAT()</h4>Torna o segmento de memória utilizável. (Anexa a memória ao processo)

<h3>Syscalls de E/S</h3>
<p>
	A aplicação tenta abrir um arquivo inicialmente inexiste no disco (caso exista a aplicação vai sobreescrever seu conteúdo), cria o arquivo e escreve uma mensagem nele. Fecha o arquivo. Em seguida, abre o arquivo novamente, recupera a informação guardada no arquivo e exibe em tela.
</p>
<h4>OPEN()</h4>Realiza a abertura de um arquivo em disco.
<h4>CREAT()</h4>Cria um arquivo no disco.
<h4>WRITE()</h4>Escreve um número pré definido de bytes no arquivo (ou saida padrão).
<h4>READ()</h4>Lê um número pre-definido de bytes do arquivo (ou entrada padrão).

<h2>Parte 2</h2>
<h3>CPU-bound</h3>
<p>
	Para esta parte, desenvolvemos uma aplicação que verifica todos os números que são primos ou não no intervalo de 5000 a 30000. Apesar do intervalo ser fixo, quanto mais aumentamos os valores, notamos um estresse maior da CPU.
</p>

<h3>I/O-bound</h3>
<p>
	Para o IO-bound desenvolvemos uma aplicação que lê, caracter por caracter, o arquivo de entrada arquivo e o escreve na saída padrão. Como no exemplo anterior, quanto maior o tamanho do arquivo (em quantidade de caracteres), notamos um estresse maior do I/O.
</p>
<br/>

<h1>TRABALHO II</h1>
<a href = "https://www.youtube.com/watch?v=raLr1-DT8aU&t=2s">Link video trabalho 2</a>
<p>
	Para compilar:
	gcc example.c -o example -lpthread <br/>
	./example <br/>
</p>
<p>
	O trabalho 2 é uma demonstração e resolução de um problema clássico quando o assunto é paralelismo: o problema dos produtores e consumidores. Basicamente o problema ocorre quando as threads não estão sincronizadas. <br/>
	Imagine a seguinte situação:
	<ul>
		<li>Produtor insere na posição 0 do buffer o elemento X.</li>
		<li>Consumidor utiliza o elemento X da posição 0 do buffer liberando a posição para que outro elemento seja inserido.</li>
		<li>Como as threads não são sincronizadas, de modo paralelo à ação anterior, o produtor insere na posição 1 do buffer o elemento Y.</li>
		<li>Note que temos dois problemas até aqui:</li>
			<ul>
				<li>Produtor não sabe que o elemento X da posição 0 do buffer foi consumido (e caso for inserir novo elemento, irá inserir na posição 2 do buffer).</li>
				<li>Consumidor não sabe que elemento Y foi inserido na posição 1 do buffer (e caso for remover algum elemento será na posição 0 do buffer).</li>
		</ul>
	</ul>
	Para resolver este problema devemos sincronizar as threads, de modo que o produtor e consumidor não percam dados por sobreposição e nem tentem utilizar lixo. Para a sincronização ultilizaremos uma das propostas de soluções de exclusão mutua, os semáforos. <br/>
	Esta solução consiste em utilizar uma variável (interira ou boleana) para determinar se deve produzir ou se deve consumir. Note que as operações de manipulação desta variável devem ser de modo não-paralelo, caso contrário, voltaríamos ao problema inicial. Estas operações onde apenas uma thread por vez pode realizar uma manipulação das variáveis (semáforo), são chamadas de operações atômicas. <br/>
	Então a solução proposta é a seguinte: quando o produtor inserir algum elemento no buffer, utilizando de uma operação atômica, ele atualiza a posição do semáforo. De modo similar, quando o consumidor for remover um elemento do buffer, utilizar uma operação atômica e atualiza o semáforo. <br/>
	Note que desta forma torna-se possível saber se o buffer está vazio (e portanto não se pode consumir) ou cheio (não sendo possível produzir mais). <br/>
</p>
<br/>

<h1>TRABALHO III</h1>
<h3>Simulador de gerenciamento de memória virtual com paginação</h3>
<a href = "https://www.youtube.com/watch?v=iwPrGIO2NL0&t=1151s">Link video trabalho 3</a>
<p>
	Para compilar:
	g++ *.cpp -o main<br/>
	./main <br/>
	
	Deve ser escolhido o tamanho das páginas, o padrão está definito para 4 bytes.
	
	Em seguida deve ser escolhido o algoritmo de substituição de páginas.
	LRU: 01
	Clock: 02

	Para as operações com os processos, são aceitos os comandos:
    C: cria um novo processo
    K: termina um processo
    P: imprime a situação atual da memória ram e o disco
    S: imprime a lista de processos na memória virtual
    W: imprime a lista de processos em espera
    O: faz uma ooperação de leitura/escrita ou entrada/saída de um processo
    F: imprime as informações sobre um processoo
    H: imprime uma lista de ajuda em relação aos comandos
    E: sai do simulador
</p>
<p>
	
</p>
<br/>
