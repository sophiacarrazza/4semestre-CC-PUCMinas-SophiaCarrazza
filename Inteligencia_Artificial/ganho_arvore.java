import java.util.*;

public class ganho_arvore {

    public static void main(String[] args) {
        // Definindo o conjunto de dados
        String[][] data = {
                { "Sim", "Não", "Não", "Sim", "Alguns", "RRR", "Não", "Sim", "Francês", "0-10", "Sim" },
                { "Sim", "Não", "Não", "Sim", "Cheio", "R", "Não", "Não", "Tailandês", "30-60", "Não" },
                { "Não", "Sim", "Não", "Não", "Alguns", "R", "Não", "Não", "Hamburger", "0-10", "Sim" },
                { "Sim", "Não", "Sim", "Sim", "Cheio", "R", "Sim", "Não", "Tailandês", "out/30", "Sim" },
                { "Sim", "Não", "Sim", "Não", "Cheio", "RRR", "Não", "Sim", "Francês", ">60", "Não" },
                { "Não", "Sim", "Não", "Sim", "Alguns", "RR", "Sim", "Sim", "Italiano", "0-10", "Sim" },
                { "Não", "Sim", "Não", "Não", "Nenhum", "R", "Sim", "Não", "Hamburger", "0-10", "Não" },
                { "Não", "Não", "Não", "Sim", "Alguns", "RR", "Sim", "Sim", "Tailandês", "0-10", "Sim" },
                { "Não", "Sim", "Sim", "Não", "Cheio", "R", "Sim", "Não", "Hamburger", ">60", "Não" },
                { "Sim", "Sim", "Sim", "Sim", "Cheio", "RRR", "Não", "Sim", "Italiano", "out/30", "Não" },
                { "Não", "Não", "Não", "Não", "Nenhum", "R", "Não", "Não", "Tailandês", "0-10", "Não" },
                { "Sim", "Sim", "Sim", "Sim", "Cheio", "R", "Não", "Não", "Hamburger", "30-60", "Sim" }
        };

        String[] labels = { "Alternativo", "Bar", "Sex/Sab", "fome", "Cliente", "Preço", "Chuva", "Res", "Tipo",
                "Tempo", "conc" };
        String targetAttribute = "conc";

        // Calcular a entropia inicial
        double entropyS = calculateEntropy(data, targetAttribute, labels);

        // Calcular o ganho de informação para cada atributo
        for (String attribute : labels) {
            if (!attribute.equals(targetAttribute)) {
                double infoGain = entropyS - calculateConditionalEntropy(data, attribute, targetAttribute, labels);
                System.out.println("Ganho de Informação para " + attribute + ": " + infoGain);
            }
        }
    }

    private static double calculateEntropy(String[][] data, String targetAttribute, String[] labels) {
        int targetIndex = getIndex(targetAttribute, labels);
        Map<String, Integer> frequency = new HashMap<>();
        for (String[] row : data) {
            frequency.put(row[targetIndex], frequency.getOrDefault(row[targetIndex], 0) + 1);
        }
        double entropy = 0.0;
        for (String key : frequency.keySet()) {
            double proportion = (double) frequency.get(key) / data.length;
            entropy -= proportion * (Math.log(proportion) / Math.log(2));
        }
        return entropy;
    }

    private static double calculateConditionalEntropy(String[][] data, String attribute, String targetAttribute,
            String[] labels) {
        int attributeIndex = getIndex(attribute, labels);
        int targetIndex = getIndex(targetAttribute, labels);
        Map<String, Map<String, Integer>> frequency = new HashMap<>();
        for (String[] row : data) {
            String attributeValue = row[attributeIndex];
            String targetValue = row[targetIndex];
            frequency.putIfAbsent(attributeValue, new HashMap<>());
            frequency.get(attributeValue).put(targetValue,
                    frequency.get(attributeValue).getOrDefault(targetValue, 0) + 1);
        }

        double conditionalEntropy = 0.0;
        for (String attributeValue : frequency.keySet()) {
            double subsetEntropy = 0.0;
            int subsetSize = 0;
            for (String targetValue : frequency.get(attributeValue).keySet()) {
                int count = frequency.get(attributeValue).get(targetValue);
                subsetSize += count;
                double proportion = (double) count / data.length;
                subsetEntropy -= proportion * (Math.log(proportion) / Math.log(2));
            }
            conditionalEntropy += ((double) subsetSize / data.length) * subsetEntropy;
        }

        return conditionalEntropy;
    }

    private static int getIndex(String attribute, String[] labels) {
        for (int i = 0; i < labels.length; i++) {
            if (labels[i].equals(attribute)) {
                return i;
            }
        }
        return -1; // should never happen if the attribute exists in labels
    }
}
