import heapq  # Usado para implementar a heap (fila de prioridade)

class Solution:
    def getSkyline(self, buildings):
        # Lista de eventos: cada prédio gera dois eventos
        events = []
        for l, r, h in buildings:
            # Evento de início do prédio com altura negativa para representar início
            events.append((l, -h, r))
            # Evento de fim do prédio com altura 0 (para facilitar remoção)
            events.append((r, 0, 0))

        # Ordenamos os eventos:
        # 1. Por x (posição da esquerda ou direita)
        # 2. Em caso de empate: inícios antes de fins (altura negativa antes de 0)
        events.sort()

        # Heap de prédios ativos (max-heap simulada com valores negativos)
        # Cada elemento é (altura negativa, fim do prédio)
        heap = [(0, float('inf'))]  # Começa com o "piso" da cidade (altura 0 infinita)
        prev_height = 0  # Altura anterior da silhueta
        result = []  # Lista de pontos-chave (x, altura)

        # Processa cada evento da esquerda para a direita
        for x, neg_h, r in events:
            # Remove do heap os prédios que já acabaram antes do ponto atual
            while heap and heap[0][1] <= x:
                heapq.heappop(heap)

            # Se for início de prédio (altura negativa), adiciona à heap
            if neg_h != 0:
                heapq.heappush(heap, (neg_h, r))

            # A altura atual é a maior altura ativa (topo do heap)
            current_height = -heap[0][0]

            # Se a altura mudou em relação ao último ponto, adiciona novo ponto-chave
            if current_height != prev_height:
                result.append([x, current_height])
                prev_height = current_height  # Atualiza altura anterior

        # Retorna os pontos que formam o contorno da silhueta
        return result
