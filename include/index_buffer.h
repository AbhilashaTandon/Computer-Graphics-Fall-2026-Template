#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

class IndexBuffer {
      private:
        unsigned int id;
        unsigned int count;

      public:
        IndexBuffer(const unsigned int *data, unsigned int count);
        // count is num indices
        ~IndexBuffer();

        void Bind() const;
        void Unbind() const;

        inline unsigned int GetCount() const { return count; }
};

#endif
