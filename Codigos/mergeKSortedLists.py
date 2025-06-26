# Definição do nó da lista encadeada (padrão LeetCode)
class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

class Solution:
    def mergeKLists(self, lists):
        # Função auxiliar para mesclar duas listas ordenadas
        def mergeTwoLists(l1, l2):
            # Cria um nó fictício que servirá como cabeça da lista mesclada
            dummy = ListNode(0)
            current = dummy  # Ponteiro que vai construir a nova lista

            # Percorre as duas listas enquanto ambas tiverem elementos
            while l1 and l2:
                if l1.val <= l2.val:
                    # O menor valor atual é de l1, então adicionamos ele na lista final
                    current.next = l1
                    l1 = l1.next  # Avança l1
                else:
                    # O menor valor atual é de l2, então adicionamos ele na lista final
                    current.next = l2
                    l2 = l2.next  # Avança l2
                current = current.next  # Avança o ponteiro da lista final

            # Quando uma das listas acabar, liga o restante da outra diretamente
            current.next = l1 if l1 else l2

            # Retorna a cabeça da nova lista (ignorando o nó fictício)
            return dummy.next

        # Caso a lista de listas esteja vazia
        if not lists:
            return None

        # Estratégia de dividir e conquistar:
        # Mescla as listas de duas em duas até restar apenas uma
        while len(lists) > 1:
            merged = []  # Lista temporária para armazenar os resultados das mesclagens

            # Percorre as listas em pares
            for i in range(0, len(lists), 2):
                l1 = lists[i]  # Primeira lista do par
                # Segunda lista do par (se existir)
                l2 = lists[i + 1] if i + 1 < len(lists) else None
                # Mescla o par e adiciona à lista temporária
                merged.append(mergeTwoLists(l1, l2))

            # Atualiza a lista principal com as listas mescladas
            lists = merged

        # Ao final, restará apenas uma lista mesclada
        return lists[0]
