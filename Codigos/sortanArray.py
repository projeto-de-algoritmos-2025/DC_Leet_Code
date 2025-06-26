class Solution:
    def sortArray(self, nums):
        # Função principal de ordenação usando Merge Sort
        def merge_sort(arr):
            # Caso base: se o array tiver 0 ou 1 elemento, já está ordenado
            if len(arr) <= 1:
                return arr

            # Dividindo o array ao meio
            mid = len(arr) // 2
            # Ordena a metade esquerda recursivamente
            left = merge_sort(arr[:mid])
            # Ordena a metade direita recursivamente
            right = merge_sort(arr[mid:])

            # Combina (merge) as duas metades ordenadas
            return merge(left, right)

        # Função auxiliar para mesclar dois arrays ordenados
        def merge(left, right):
            result = []  # Lista resultante da fusão ordenada
            i = j = 0    # Ponteiros para percorrer left e right

            # Compara elementos de left e right, inserindo o menor no resultado
            while i < len(left) and j < len(right):
                if left[i] <= right[j]:
                    result.append(left[i])
                    i += 1
                else:
                    result.append(right[j])
                    j += 1

            # Adiciona o que sobrou da lista esquerda (se houver)
            result.extend(left[i:])
            # Adiciona o que sobrou da lista direita (se houver)
            result.extend(right[j:])

            return result

        # Chama a função de ordenação sobre o array original
        return merge_sort(nums)
