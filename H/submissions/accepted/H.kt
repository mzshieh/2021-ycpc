fun main() {
    val (n, m, _) = readLine()!!.split(" ").map{ it.toInt() }
    val training = HashSet<List<Int>>()
    for (i in 1..n) {
        training.add(readLine()!!.split(" ").map{ it.toInt()})
    }
    for (i in 1..m) {
        val buf = readLine()!!.split(" ").map{ it.toInt() }
        if (training.contains(buf))
            println("BAD")
        else
            println("GOOD")
    }
}
