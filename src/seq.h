#ifndef SEQ_H_INCLUDED
#define SEQ_H_INCLUDED

#include <stdint.h>
#include <memory>
#include <string>
#include <vector>

#include "bioparser/bioparser.hpp"
#include "kmer_index.h"

class Seq;
typedef std::vector<std::unique_ptr<Seq>> SequencesP;
typedef std::vector<Seq> Sequences;

class Seq {
public:
    Seq(const std::string& name, const std::string& seq,
	const std::string& qual, double score);
    ~Seq() = default;

    const std::string& Name() const { return name; }
    void SetName(const std::string& name) { this->name = name; }

    const std::string& Str() const { return seq; }
    void SetStr(const std::string& seq) { this->seq = seq; }

    const std::string& Qual() const { return qual; }
    void SetQual(const std::string& qual) { this->qual = qual; }

    double Score() const { return score; }

    void SetScore(const double score) { this->score = score; }
    double ErrorRate() const { return errorRate; }

    void SetErrorRate(const double errorRate) { this->errorRate = errorRate; }

    template <class Archive>
    void serialize(Archive& archive)
    {
	archive(name, seq, qual, score, errorRate);
    }

    friend bioparser::FastaParser<Seq>;
    friend bioparser::FastqParser<Seq>;
    Seq(const Seq& o)
    {
	name = o.name;
	seq = o.seq;
	qual = o.qual;
	score = o.score;
	errorRate = o.errorRate;
    };
    Seq(){

    };
    const Seq& operator=(const Seq& t)
    {
	name = std::string(t.name);
	seq = std::string(t.seq);
	qual = std::string(t.qual);
	score = t.score;
	errorRate = t.errorRate;
	return *this;
    };

private:
    Seq(const char* name, uint32_t name_size, const char* data,
	uint32_t data_size, const char* quality, uint32_t quality_size);

    std::string name{};
    std::string seq{};
    std::string qual{};
    double score{};
    double errorRate{};
};

#endif
