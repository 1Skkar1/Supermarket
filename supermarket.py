import math, random
from estruturas import *

# == Simulador de supermercado == #

# = = = Tipo cliente = = = #
#
# O tipo cliente armazena informacao referente ao numero de items que um cliente
# pretende comprar e o seu tempo de entrada.

class cliente:
    
    # Construtor:
    
    def __init__(self, items, entrada):
        ''' cliente : int x int -> cliente
            cliente(n, t) devolve um cliente com n items a comprar que foi para
            as caixas no instante t.'''
        
        self.__items = items
        self.__entrada = entrada
        
    # Selectores:
        
    def artigos(self):
        ''' artigos : cliente -> int
            artigos(c) devolve o numero de artigos a comprar pelo cliente c.'''
        
        return self.__items
    
    def tempo_entrada(self):
        ''' tempo_entrada : cliente -> int
            tempo_entrada(c) devolve o instante em que o cliente c se dirigiu
            as caixas.'''
        
        return self.__entrada
    
    # Transformador de saida:
    
    def __repr__(self):
        ''' __repr__ : cliente -> str
            __repr__(c) devolve a representacao externa de um cliente, que e 
            dada por:
            
            [ <items> : <entrada> ] '''
        
        return '[' + str(self.__items) + ':' + str(self.__entrada) + ']'
    
# = = = Tipo caixa = = = #
#
# O tipo caixa mantem a informacao referente a uma das caixas do supermercado.
# Em particular, mantem informacao sobre:
#
# - os clientes na fila dessa caixa
# - uma "estimativa" tempo em que a caixa estara disponivel
# - o numero de clientes ja'atendidos por essa caixa
# - o numero de produtos processados nessa caixa
# - o tempo total de espera nessa caixa
# - o numero da caixa
# - a "velocidade" de processamento da caixa, isto e', quantos produtos processa
#   por unidade de tempo

class caixa:
    
    # Construtor: 
    
    def __init__(self, numero):
        ''' caixa : int -> caixa
            caixa(n) devolve o objecto correspondente a caixa com o numero n.'''
        
        self.__fila = fila()
        self.__eta = 0
        self.__clientes = 0
        self.__produtos = 0
        self.__espera = 0
        self.__numero = numero
        self.__velocidade = int(random.random() * 5) + 1
        
    # Modificadores:
    
    def disponivel(self, valor):
        ''' disponivel : caixa x int -> {}
            disponivel(c, t) actualiza o instante em que a caixa c estara 
            disponivel para t.'''
        
        self.__eta = valor
        
    def cliente_atendido(self):
        ''' cliente_atendido : caixa -> {}
            cliente_atendido(c) actualiza o numero de clientes atendidos na 
            caixa c para mais 1.'''
        
        self.__clientes += 1
        
    def actualiza_produtos(self, produtos):
        ''' actualiza_produtos : caixa x int -> {}
            actualiza_produtos(c, n) actualiza o numero de produtos processados 
            na caixa c para mais n.'''
        
        self.__produtos += produtos
        
    def actualiza_espera(self, valor):
        ''' actualiza_espera : caixa x t -> {}
            actualiza_espera(c, t) actualiza o tempo de espera na caixa c para
            mais t.'''
        
        self.__espera += valor
        
    def remove_cliente(self):
        ''' remove_cliente : caixa -> {}
            remove_cliente(c) retira um cliente da fila da caixa c.'''
        
        self.__fila.retira()
        
    # Selectores
    
    def fila_caixa(self):
        ''' fila_caixa : caixa -> fila
            fila_caixa(c) devolve a fila associada 'a caixa c.'''
        
        return self.__fila
    
    def numero(self):
        ''' numero : caixa -> int
            numero(c) devolve o numero da caixa c.'''
        
        return self.__numero
    
    def pronta(self):
        ''' pronta : caixa -> int
            pronta(c) devolve a estimativa de quando a caixa c estara pronta.'''
        
        return self.__eta
    
    def clientes(self):
        ''' clientes : caixa -> int
            clientes(c) devolve o numero de clientes atendidos na caixa c.'''
        
        return self.__clientes
    
    def produtos(self):
        ''' produtos : caixa -> int
            produtos(c) devolve o numero de produtos processados na caixa c.'''
        
        return self.__produtos
    
    def espera(self):
        ''' espera : caixa -> int
            espera(c) devolve o tempo total de espera na caixa c.'''
        
        return self.__espera
    
    def tempo_processamento(self):
        ''' tempo_processamento : caixa -> int
            tempo_processamento(c) devolve o numero de produtos processados por
            unidade de tempo na caixa c.'''
        
        return self.__velocidade
    
    # Reconhecedores
    
    def vazia(self):
        ''' vazia : caixa -> logico
            vazia(c) devolve True caso a caixa c esteja vazia (sem clientes) e
            False em caso contrario.'''
        
        return self.__fila.vazia()
    
    # Transformador de saida
        
    def __repr__(self):
        ''' __repr__ : caixa -> str
            __repr__(c) devolve a string correspondente 'a representacao externa
            da caixa c, dada por:
            
            Caixa <numero> (<tempo>): <fila>'''
        
        rep = 'Caixa ' + str(self.__numero) + \
              ' ('     + str(self.__eta)    + '): ' + \
              str(self.__fila)
        
        return rep
    

# Operacoes auxiliares

def trata_clientes(passo, lista_caixas):
    ''' trata_clientes : int x lista -> {}
        trata_clientes(t, l) percorre as caixas na lista l, actualizando as
        respectivas listas de clientes, quando necessario (isto e', processando
        os clientes que ja' estao na caixa tempo suficiente para estarem
        despachados.'''
    
    def trata_primeiro(passo, caixa_actual):
        ''' trata_primeiro : int x caixa -> {}
            trata_primeiro(t, c) verifica se o primeiro cliente da caixa c
            (caso exista) ja' esta' despachado e actualiza a informacao na
            caixa nesse caso.'''
        
        # Obtem informacao sobre o primeiro cliente na fila
        
        cliente = caixa_actual.fila_caixa().inicio()
        espera  = passo - caixa_actual.pronta()
        processados = espera * caixa_actual.tempo_processamento()
        
        # Caso o primeiro cliente da fila esteja despachado, actualiza 
        # informacao da caixa
        
        if processados >= cliente.artigos():
            caixa_actual.disponivel(passo + 1)
            caixa_actual.cliente_atendido()
            caixa_actual.actualiza_produtos(cliente.artigos())
            caixa_actual.actualiza_espera(passo - cliente.tempo_entrada())
            caixa_actual.remove_cliente()
            print('--> Cliente atendido na caixa %i' % caixa_actual.numero())            
            
    # Percorre caixas e vai processando uma a uma
    
    for c in lista_caixas:
        if c.vazia():
            c.disponivel(passo)
        else:
            trata_primeiro(passo, c)      
    
def caixas_cheias(lista_caixas):
    ''' caixas_cheias : lista -> logico
        caixas_cheias(l) devolve True se alguma caixa na lista l tiver clientes
        e False em caso contrario.'''
    
    for c in lista_caixas:
        if not c.vazia():
            return True
        
    return False

def mostra_caixas(lista_caixas):
    ''' mostra_caixas : lista -> {}
        mostra_caixas(l) mostra para o ecra a representacao externa de cada uma 
        das caixas em l.'''
    
    for c in lista_caixas:
        print(c)
    
def processa_resultados(caixas):
    ''' processa_resultados : lista -> {}
        processa_resultados(l) escreve para o ecra as estatisticas de cada caixa
        na lista l.'''
    
    for c in caixas:
        print('Caixa %i' % c.numero(), 
              '(%i produtos por ciclo)' % c.tempo_processamento())
        
        if c.clientes() != 0:
            print('%i clientes atendidos,' % c.clientes(), \
                  'media %.1f produtos/cliente' % (c.produtos()/c.clientes()))
        else:
            print('%i clientes atendidos' % c.clientes())


def simulador(afluencia, apetencia, n_caixas, n_ciclos):
    ''' simulador : int x int x int x int -> {}
        simulador(af, ap, n, t) simula um supermercado com n caixas durante 
        t ciclos, em que os clientes sao gerados com uma afluencia af e uma
        apetencia ap.'''
    
    # Inicializa caixas
    
    caixas = []
    for i in range(n_caixas):
        caixas = caixas + [caixa(i + 1)]
        
    # Inicia simulacao
    
    for t in range(1, n_ciclos + 1):

        print('== CICLO %i ==' % t)
        
        # Processa clientes nas caixas
        
        trata_clientes(t, caixas)
        
        # Cria novo cliente aleatoriamente
         
        if random.random() <= afluencia / 100:
            
            # Cria numero de produtos aleatoriamente
            
            produtos = random.randint(1, 3 * apetencia)            
            novo_cliente = cliente(produtos, t)
            
            print('--> Criado cliente com %i produtos.' % produtos)
            
            # Selecciona caixa aleatoriamente
            
            caixa_escolhida = random.randint(1, n_caixas)
            
            # Coloca cliente na fila
            
            caixas[caixa_escolhida - 1].fila_caixa().coloca(novo_cliente)
            
        mostra_caixas(caixas)
        
    # Fecho de simulacao
    
    print('== FECHO DE CAIXAS ==')    
    t = n_ciclos + 1
    
    while caixas_cheias(caixas):
        print('== CICLO %i ==' % t)        
        trata_clientes(t, caixas)
        mostra_caixas(caixas)
        t = t + 1
        
    processa_resultados(caixas)